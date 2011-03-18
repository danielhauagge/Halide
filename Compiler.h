#ifndef COMPILER_H
#define COMPILER_H

#include "IRNode.h"
#include "FImage.h"

class Compiler {
public:
    
    // Compile a gather statement. e.g:
    // out(x, y, c) = 37*im(x+y, y*4, c);
    // 
    // Right now it assumes the following in order to vectorize across x for all loads. 
    //
    // 1) The bounds of X are a multiple of 4
    //
    virtual void compile(FImage *im);
    virtual void run() = 0;

    // TODO: Compile a reduction

    // TODO: Compile a scan

    // TODO: unify the above into a single compile which detects the
    // appropriate way to compile the evaluation of an FImage given
    // its definitions
    
protected:
    NodeData<Variable>* varData(size_t i) { return vars[i]->data<Variable>(); }
    
    virtual void compilePrologue() = 0;

    // Compile a single definition
    // Gather all descendents of a node with a particular op
    virtual void collectInputs(IRNode::Ptr node, OpCode op, IRNode::PtrSet &nodes);
    
    virtual void compileDefinition(FImage *im, int definition);
    virtual void compileBody(vector<IRNode::Ptr> code) = 0;
    virtual void compileEpilogue() = 0;
    
    vector<IRNode::Ptr> roots;
    vector<IRNode::Ptr> vars;
    
    vector<int> vectorWidth;
    vector<int> unroll;
};

#endif
