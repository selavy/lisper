#include "abstract_syntax_tree.h"
#include <iostream>
#include <stack>

AbstractSyntaxTree::Node::Node()
    : data_()
    , left_(nullptr)
    , right_(nullptr)
{
}

AbstractSyntaxTree::Node::Node(ObjectPtr data)
    : data_(std::move(data))
    , left_(nullptr)
    , right_(nullptr)
{
}

void AbstractSyntaxTree::Node::print(std::ostream& os) const
{
    if (data_) {
        os << *data_;
    }
    else {
        os << "(null)";
    }
    // if (data_) {
    //     if (left_) {
    //         os << *left_ << " -> ";
    //     }
    //     if (right_) {
    //         os << *right_ << " -> ";
    //     }        
    //     os << *data_ << " -> ";
    // }
    // else {
    //     os << "(null)";
    // }
}

AbstractSyntaxTree::AbstractSyntaxTree()
    : root_()
    , factory_()
    , moveRight_(true)
{
}

void AbstractSyntaxTree::addToken(std::string token)
{
    std::cout << "Adding token: " << token << "\n";
    if (token == "(") {
        // begin expr
        // moveRight_ = false;
    }
    else if (token == ")") {
        // end expr
        // moveRight_ = false;
    }
    else {
        ObjectPtr object{std::move(factory_.create(token))};
        std::cout << "Object returned by factory: ";
        if (object) std::cout << *object;
        else std::cout << "(null)";
        std::cout << "\n";

        if (object) {
            addObject(root_, std::move(object));
        }
    }
}

void AbstractSyntaxTree::print(std::ostream& os) const
{
    if (!root_) {
        os << "(null)";
    }
    else {
        printTree(os, root_);
    }
}

void AbstractSyntaxTree::printTree(std::ostream& os, Node* node) const
{
    std::stack<Node*> stack;
    stack.push(node);
    while (!stack.empty()) {
        Node *curr = stack.top();
        stack.pop();

        if (curr) {
            os << *curr << " ";
            if (curr->left_) {
                stack.push(curr->left_);
            }
            if (curr->right_) {
                stack.push(curr->right_);
            }
        }
    }
}

void AbstractSyntaxTree::addObject(Node*& node, ObjectPtr object)
{
    if (!node) {
        node = new Node(std::move(object));
    }
    else if (!node->left_) {
        addObject(node->left_, std::move(object));
    }
    else {
        addObject(node->right_, std::move(object));
    }
}

std::ostream& operator<<(std::ostream& os, const AbstractSyntaxTree::Node& node)
{
    node.print(os);
    return os;
}

std::ostream& operator<<(std::ostream& os, const AbstractSyntaxTree& ast)
{
    ast.print(os);
    return os;
}
