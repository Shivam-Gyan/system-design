//  here we are going to design the system for google docs


#include<iostream>
#include<bits/stdc++.h>
using namespace std;

// BAD design of google docs 

// class Document{

//     private:
//         vector<string> documentElements;
//         string renderDocument;

//     public:
//         void add_text(string text){
//             documentElements.push_back(text);
//         }

//         void add_image(string imagePath){
//             documentElements.push_back(imagePath);
//         }

//         void render_document(){
            
//             if(!documentElements.empty()){

//                 string result;
//                 for(auto element: documentElements){
                   
//                     if(element.size() > 4 && element.substr(element.size() - 4) == ".png"){
//                         result +="Image: " + element + "\n";
//                     } else {
//                         result += "Text: " + element + "\n";
//                     }
//                 }
//                 renderDocument = result;
//             }
//         }


//         void display_document(){
//             if(!renderDocument.empty()){
//                 cout << renderDocument << endl;
//             }
//         }

// };

// int main(){

//     Document Doc;

//     Doc.add_text("hello world");
//     Doc.add_image("picture.png");
//     Doc.add_text("I am shivam gupta");
//     Doc.render_document();
//     Doc.display_document();

//     return 0;
// }



// Good design of google docs

class Element{

    public:
        virtual string render() = 0;
        virtual ~Element() = default;
};

// implementing text element and image element using abstract class Element
class TextElement: public Element{
    private:
        string text;

    public:
    TextElement(string text): text(text){}

    string render() override{
        return text;
    }

    ~TextElement() = default;
};

class ImageElement: public Element{
    private:
        string imagePath;

    public:
    ImageElement(string imagePath): imagePath(imagePath){}
    
    string render() override{
        return "[ Image : " + imagePath + " ]";
    }
    ~ImageElement() = default;
};

class NewLineElement: public Element{
    public:
        string render() override{
            return "\n";
        }
};

class NewTabElement: public Element{
    public:
        string render() override{
            return "\t";
        }
};


// has a relationship with element class and it can have multiple elements in the document
class Document{
    private:
        vector<Element*> elements;
    
    public:
        void add_element(Element* element){
            elements.push_back(element);
        }

        vector<Element*> get_elements(){
            return elements;
        }
};

// has a relationship with document class and it is responsible for rendering the document
class RenderElement{
    private:
        Document* document;
    
    public:
        RenderElement(Document* document): document(document){}

        string render(){
            string result;
            for(auto element: document->get_elements()){
                result += element->render();
            }
            return result;
        }
};
 
// save and load the document data using file storage or database storage using the persistence interface
class Persistence{
    public:
        virtual void save(string data) = 0;
        virtual string load() = 0;
        virtual ~Persistence() = default;
};

class FileStorage: public Persistence{
    private:
        string filePath;

    public:
        FileStorage(string filePath): filePath(filePath){}

        void save(string data) override{
            ofstream outFile(filePath);
            if(outFile.is_open()){
                outFile << data;
                outFile.close();
            }
        }

        string load() override{
            ifstream inFile(filePath);
            string data, line;
            if(inFile.is_open()){
                while(getline(inFile, line)){
                    data += line + "\n";
                }
                inFile.close();
            }
            return data;
        }
};

class DBStorage: public Persistence{
    private:
        string connectionString;

    public:
        DBStorage(string connectionString): connectionString(connectionString){}

        void save(string data) override{
            // code to save data to database using connection string
        }

        string load() override{
            // code to load data from database using connection string
            return "";
        }
};

//  it will create a new Element pointer object based on the type of element we want to add
enum class ElementType { TEXT, IMAGE, NEW_LINE, NEW_TAB };

//  Fcatory Pattern to create elements based on the type of element we want to add
class ElementFactory{
    public:
        static Element* create_element(ElementType type,string content =""){

            switch(type){
                case ElementType::TEXT:
                    return new TextElement(content);
                case ElementType::IMAGE:
                    return new ImageElement(content);
                case ElementType::NEW_LINE:
                    return new NewLineElement();
                case ElementType::NEW_TAB:
                    return new NewTabElement();
                default:
                    return nullptr;
            }
        }
};


class Editor{
    private:
        Document* document;
        RenderElement* renderer;
        Persistence* storage;

        string currentDocumentData;

    public:
        Editor(Document* document, RenderElement* renderer, Persistence* storage): document(document), renderer(renderer), storage(storage){
            cout << "Editor initialized successfully!" << endl;
        }

        // it will create a new element based on the type of element we want to add and add it to the document
        void add_element_to_doc(ElementType type, string content = ""){
            Element* element = ElementFactory::create_element(type, content);
            if(element){
                document->add_element(element);
                cout << "Element added to document successfully!" << endl;
            }
        }

        void render_document(){
            currentDocumentData = renderer->render();
            cout << "Rendered Document:\n" << currentDocumentData << endl;
        }

        void save_document(){
            if(!currentDocumentData.empty()){
                storage->save(currentDocumentData);
                cout << "Document saved successfully!" << endl;
            }
        }

        void load_document(){
            string data = storage->load();
            if(!data.empty()){
                // code to parse the loaded data and populate the document with elements
                cout << "Loaded Document Data:\n " << data << endl;
            }else{
                cout << "No document data found to load." << endl;
            }
        }
};

int main(){

    Document* doc = new Document();
    RenderElement* renderer = new RenderElement(doc);
    FileStorage* fileStorage = new FileStorage("document.txt");

    Editor* editor = new Editor(doc, renderer, fileStorage);

    editor->add_element_to_doc(ElementType::TEXT, "Hello, World!");
    editor->add_element_to_doc(ElementType::NEW_LINE);
    editor->add_element_to_doc(ElementType::TEXT, "I am Shivam Gupta. Learning system design.");
    editor->add_element_to_doc(ElementType::NEW_LINE);
    editor->add_element_to_doc(ElementType::IMAGE, "picture.png");
    editor->add_element_to_doc(ElementType::NEW_LINE);
    editor->add_element_to_doc(ElementType::TEXT, "This is a simple document editor.");
    editor->render_document();
    editor->save_document();

    editor->load_document();

    delete editor;
    delete fileStorage;
    delete renderer;
    delete doc;

    return 0;
}