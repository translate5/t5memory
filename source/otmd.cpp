
//#define GLOG_NO_ABBREVIATED_SEVERITIES

#include <iostream>
#include <csignal>
#include <cstdlib>
#include <chrono>
#include <thread>
#include <unistd.h>
#include <folly/portability/GFlags.h>

static bool ValidatePort(const char* flagname, int32_t value) {
   if (value > 0 && value < 32768)   // value is ok
     return true;
   printf("Invalid value for --%s: %d\n", flagname, (int)value);
   return false;
}

DEFINE_int32(port, 4080, "What port to listen on");
DEFINE_validator(port, &ValidatePort);

/*
static bool ValidateLocalhostonly(const char* flagname, int32_t value) {
   if (value == 0 || value == 1)   // value is ok
     return true;
   printf("Invalid value for --%s: %d, use only 0 or 1\n", flagname, (int)value);
   return false;
}//*/

DEFINE_bool(localhostonly, false, "Should we use localhost or external address for service");
//DEFINE_int32(localhostonly, 0, "Should we use localhost or external address for service");
//DEFINE_validator(localhostonly, &ValidateLocalhostonly);

DEFINE_string(servicename, "t5memory", "Sets service name to use in url");

static bool ValidateTriplesThreshold(const char* flagname, int32_t value) {
   if (value >= 0 && value <= 100)   // value is ok
     return true;
   printf("Invalid value for --%s: %d, should be [0...100]\n", flagname, (int)value);
   return false;
}

DEFINE_int32(triplesthreshold, 33, "Sets threshold to pre fuzzy filtering based on hashes of neibour tokens");
DEFINE_validator(triplesthreshold, &ValidateTriplesThreshold);


static bool ValidateTimeout(const char* flagname, int32_t value) {
   if (value >= 0 && value <= 10000)   // value is ok
     return true;
   printf("Invalid value for --%s: %d, should be [0...10000]\n", flagname, (int)value);
   return false;
}

DEFINE_int32(timeout, 3600, "Sets timeout for service request handling");
DEFINE_validator(timeout, &ValidateTimeout);


static bool ValidateThreads(const char* flagname, int32_t value) {
   if (value >= 1 && value <= 100)   // value is ok
     return true;
   printf("Invalid value for --%s: %d, should be [1...100]\n", flagname, (int)value);
   return false;
}

DEFINE_int32(servicethreads, 1, "Sets amought of worker threads for service");
DEFINE_validator(servicethreads, &ValidateThreads);


static bool ValidateRAM(const char* flagname, int32_t value) {
   if (value >= 1 && value <= 10000)   // value is ok
     return true;
   printf("Invalid value for --%s: %d, should be [1...10000]\n", flagname, (int)value);
   return false;
}

DEFINE_int32(allowedram, 500, "Sets amought RAM(in MB) allowed for service to use");
DEFINE_validator(allowedram, &ValidateRAM);

static bool ValidateLOGlevel(const char* flagname, int32_t value) {
   if (value >= 0 && value <= 6)   // value is ok
     return true;
   printf("Invalid value for --%s: %d, should be [0...6]\n", flagname, (int)value);
   return false;
}

DEFINE_int32(t5loglevel, 0, "Sets t5memory log level threshold from DEVELOP(0) to TRANSACTION(6)[disabled]");
DEFINE_validator(t5loglevel, &ValidateLOGlevel);


DEFINE_bool(useconfigfile, false, "Set to use values from config file that should be located under ~/.t5memory/t5memory.conf");

//#include <glog/logging.h>
#include <execinfo.h>
#include "RestAPI/OtmMemoryService.h"
#include "opentm2/core/utilities/LogWrapper.h"
#include "cmake/git_version.h"
#include "opentm2/core/utilities/PropertyWrapper.H"
#include "EQF.H"


void handle_interrupt_sig(int sig) {
    LogMessage(TRANSACTION, "Received interrupt signal\n");
    //StopOtmMemoryService();
    LogMessage(TRANSACTION, "Stopped t5memory\n");
}

void FailureWriter(const char* data, int size){
    LogMessage(FATAL, data);
    void *array[10];
    size_t sz;

    // get void*'s for all entries on the stack
    sz = backtrace(array, 10);
    std::string backtraceStr;
    for(int i = 0; i < sz && array[i] != 0; i++){
        backtraceStr += (char*) array[i];
        backtraceStr += '\n';

    }
    LogMessage2(FATAL, ":backtrace:\n",  backtraceStr.c_str());

    // print out all the frames to stderr
    //fprintf(stderr, "Error: signal %d:\n", sig);
    backtrace_symbols_fd(array, size, STDERR_FILENO);
}

/*
void CustomPrefix(std::ostream &s, const LogMessageInfo &l, void*) {
   l.
   s << l.severity[0]
   << setw(4) << 1900 + l.time.year()
   << setw(2) << 1 + l.time.month()
   << setw(2) << l.time.day()
   << ' '
   << setw(2) << l.time.hour() << ':'
   << setw(2) << l.time.min()  << ':'
   << setw(2) << l.time.sec() << "."
   << setw(6) << l.time.usec()
   << ' '
   << setfill(' ') << setw(5)
   << l.thread_id << setfill('0')
   << ' '
   << l.filename << ':' << l.line_number << "]";
}
//*/

int proxygen_server_init();
int main(int argc, char* argv[]) {
    if(FLAGS_log_dir.empty()){

//        FLAGS_log_dir = "/home/or/.t5memory/LOG/";
        FLAGS_log_dir = "/root/.t5memory/LOG/";
    }
    FLAGS_colorlogtostderr = true;
    //FLAGS_alsologtostderr = true;
    //google::InstallFailureSignalHandler();
   // google::InstallFailureWriter(FailureWriter);
    gflags::ParseCommandLineFlags(&argc, &argv, true);
    //gflags::ParseCommandLineFlags(&argc, &argv, false);
    google::InitGoogleLogging(argv[0]);//, &CustomPrefix);

    //int logLevel = 1/0;
    //WLogMessage(logLevel, "fail");
    //LOG_DEBUG_MSG() << "SOME_DEBUG_MSG";
    
    LogMessage(TRANSACTION, "Worker thread starting");
    std::thread worker(proxygen_server_init);
    worker.join();
    LogMessage(TRANSACTION, "Worker thread finished");
    
}

