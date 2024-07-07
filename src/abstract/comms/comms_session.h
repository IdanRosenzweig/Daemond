#ifndef COMMS_SESSION_H
#define COMMS_SESSION_H

struct comms_session {
    virtual int send_data(const void *buff, int cnt) = 0;
    virtual int recv_data(void* dest, int max_sz) = 0;
    virtual void terminate_session() {}
    virtual bool is_session_alive() = 0;

    virtual ~comms_session() {
        terminate_session();
    }
};

#endif //COMMS_SESSION_H
