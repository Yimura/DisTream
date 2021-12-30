#include "connection.hpp"

namespace distream
{
    Connection::Connection(connection_hdl hdl)
        : m_hdl(hdl)
    {

    }

    Connection::~Connection()
    {
        
    }

    void Connection::authenticate(std::string application_id, int shard_id)
    {
        m_application_id = application_id;
        m_shard_id = shard_id;

        m_authenticated = true;
    }

    bool Connection::is_authenticated()
    {
        return m_authenticated;
    }
}