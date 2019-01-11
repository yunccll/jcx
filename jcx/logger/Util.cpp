#include <jcx/logger/Util.h>
#include <jcx/base/Crossplatform.h>

namespace jcx { 
namespace logger {

void Util::error_to_stdout_with_strerror(const char * file, const int line, const char* msg){
    const int max_err_msg_len = 256;
    auto buffer = std::shared_ptr<char>(new char[max_err_msg_len]);
    strerror_r(errno, buffer.get(), max_err_msg_len);
    printf("ERROR %s:%d %s errno:%d,strerror:%s\n", file, line, msg, errno, buffer.get());
}

void Util::error_to_stdout(const char * file, const int line, const char* msg){
    printf("ERROR %s:%d %s\n", file, line, msg);
}


Int2StrTab::Int2StrTab(int len, int width)
:_tab(0), _len(len), _width(width){
    assert(len >= 0 && width > 0 && width <= 10);
    _tab  = create_tab(_len, _width);
}
Int2StrTab::~Int2StrTab(){
    free_two_width_tab(_tab, _len);
}

char ** Int2StrTab::create_tab(int len, int width){
    static int ten_times_tab [] = {
        1, 
        10,
        10*10,
        10*10*10, 
        10*10*10*10,
        10*10*10*10*10, 
        10*10*10*10*10*10, 
        10*10*10*10*10*10*10, 
        10*10*10*10*10*10*10*10,
    };
    char ** ret = new char *[len];
    for(int i = 0; i < len; ++i){
        ret[i] = new char[width];
//        ret[i] = new char[width+1];
        for(int j = 0; j < width; ++j){
//            printf("times : %d, width[%d], j[%d]\n", ten_times_tab[width-j], width, j);
            ret[i][j] = '0' + i/ten_times_tab[width-j-1]%10;
        }
//        ret[i][width] = 0;
//        printf("ret[i]:%s\n", ret[i]);
    }
    return ret;
}
void Int2StrTab::free_two_width_tab(char ** tab, int len){
    for( int i = len-1; i >= 0; --i){
        delete tab[i];
    }
    delete tab;
}

} //namespace logger
} //namespace jcx
