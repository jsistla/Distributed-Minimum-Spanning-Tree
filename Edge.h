#ifndef EDGE_H
#define EDGE_H

#include <queue>
#include <condition_variable>
#include <mutex>

#include "Node.h"
class Message {
    public:
        Message(int, std::string);
        int _code;
        std::string _msg;
        std::string getMessage();
        ~Message();
};

class Pipe {
    private: 
        NodeID _id;
    public: 
        std::queue<Message> _queue;
        std::mutex _mutex;
        Pipe(NodeID id);
        NodeID getID() { return _id;}
        void writeMsg(Message *msg);
        Message *readMsg();
};
// Use notify and stuff to wake the sleeping thread.


// An edge is a message passing system. Messages can be passed only between two
// nodes connected by an edge.
class Edge {
    private:
        Node *_a;
        Node *_b;
        Pipe *_pipe_a;
        Pipe *_pipe_b;
    public:
        Edge(Node *a, Node *b);
               
        Pipe * getPipeA() { return _pipe_a; }
        Pipe * getPipeB() { return _pipe_b; }
        void sendMessage(Pipe * pipe, Message *msg);
        std::condition_variable _cv;
        std::mutex _mu;
        ~Edge();
};

#endif