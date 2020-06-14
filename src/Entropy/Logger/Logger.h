namespace Entropy {

    class Logger
    {
    public:
        static void Trace(const char* msg);
        static void Info(const char* msg);
        static void Warn(const char* msg);
        static void Error(const char* msg);
        static void Fatal(const char* msg);

    private:

    };
}
