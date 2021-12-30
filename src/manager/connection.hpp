#pragma once
#include "common.hpp"

namespace distream
{
    class Connection
    {
    private:
        connection_hdl m_hdl; 

        bool m_authenticated = false;

        std::string m_application_id = "";
        int m_shard_id = -1;
        // list of guilds
        // guild contains a link to a threaded player

    public:
        Connection(connection_hdl hdl);
        ~Connection();

        void authenticate(std::string application_id, int shard_id);

        bool is_authenticated();
    };
    
}