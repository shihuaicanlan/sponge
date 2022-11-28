#include "byte_stream.hh"

// Dummy implementation of a flow-controlled in-memory byte stream.

// For Lab 0, please replace with a real implementation that passes the
// automated checks run by `make check_lab0`.

// You will need to add private members to the class declaration in `byte_stream.hh`

template <typename... Targs>
void DUMMY_CODE(Targs &&... /* unused */) {}

using namespace std;
//初始化属性列表
ByteStream::ByteStream(const size_t capacity):buffer(),buffer_max_cnt(capacity),read_cnt(0),write_cnt(0),_end_input(false){}

size_t ByteStream::write(const string &data) {
    if(_end_input)
    {
        return 0;
    }
    size_t write_size=min(data.size(),remaining_capacity());
    write_cnt+=write_size;
    buffer+=data.substr(0,write_size);
    return write_size;
}
//! \param[in] len bytes will be copied from the output side of the buffer
string ByteStream::peek_output(const size_t len) const {
    return buffer.substr(0,len);
}

//! \param[in] len bytes will be removed from the output side of the buffer
void ByteStream::pop_output(const size_t len) { 
    size_t minlen=min(len,buffer.size());
    buffer.erase(0,minlen);
    read_cnt+=minlen;
 }

//! Read (i.e., copy and then pop) the next "len" bytes of the stream
//! \param[in] len bytes will be popped and returned
//! \returns a string
std::string ByteStream::read(const size_t len) {
    std::string tempstring=peek_output(len);
    pop_output(len);
    return tempstring;
}
void ByteStream::end_input() {
        _end_input=true;
}

bool ByteStream::input_ended() const 
{ 
    return _end_input;
}

size_t ByteStream::buffer_size() const { 
    return buffer.size();
 }

bool ByteStream::buffer_empty() const { 
    return buffer.empty();
 }

bool ByteStream::eof() const {
    return _end_input&&buffer.empty();
 }

size_t ByteStream::bytes_written() const { 
    return write_cnt;
 }

size_t ByteStream::bytes_read() const { 
    return read_cnt;
 }

size_t ByteStream::remaining_capacity() const 
{ 
    return buffer_max_cnt-buffer.size();
}
