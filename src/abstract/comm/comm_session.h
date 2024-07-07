#ifndef COMM_SESSION_H
#define COMM_SESSION_H

struct comm_session {
    virtual int send_data(void* buff, int cnt) = 0;
    virtual int recv_data(void* dest, int max_sz) = 0;
    virtual void terminate_session() = 0;
    virtual bool is_session_alive() = 0;

    virtual ~comm_session() {}
};

#endif //COMM_SESSION_H
