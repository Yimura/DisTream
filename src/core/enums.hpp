namespace distream
{
    enum eEventOp
    {
        NONE = -1,
        AUTHENTICATE,
        AUTHORIZED,

        VOICE_CONNECT,

        PLAYER_LOOKUP,
        PLAYER_PAUSE,
        PLAYER_UPDATE
    };
}