#ifndef ABSTRACT_SYNTAX_TREE__H_
#define ABSTRACT_SYNTAX_TREE__H_

#include <string>
#include "object.h"
#include "object_factory.h"

class AbstractSyntaxTree
{
public:
    struct Node
    {
        ObjectPtr data_;
        Node*     left_;
        Node*     right_;

        Node();

        Node(ObjectPtr data);

        void print(std::ostream& os) const;
    };
    
public:
    AbstractSyntaxTree();

    void addToken(std::string token);

    void print(std::ostream& os) const;

private:
    void addObject(Node*& node, ObjectPtr object);

    void printTree(std::ostream& os, Node* node) const;

private:
    Node* root_;
    ObjectFactory factory_;
    bool moveRight_;
};

std::ostream& operator<<(std::ostream& os, const AbstractSyntaxTree::Node& node);

std::ostream& operator<<(std::ostream& os, const AbstractSyntaxTree& ast);

#endif // ABSTRACT_SYNTAX_TREE__H_
