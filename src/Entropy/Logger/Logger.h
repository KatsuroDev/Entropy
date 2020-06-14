namespace Entropy {

    class Logger
    {
    public:
        static void Trace(const char* msg);
        static void Info(const char* msg);
        static void Warn(const char* msg);
        static void Error(const char* msg);
        static void FATAL(const char* msg, int code = 0);

    private:

    };
}
