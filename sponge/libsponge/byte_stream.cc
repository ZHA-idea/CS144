#include "byte_stream.hh"

// Dummy implementation of a flow-controlled in-memory byte stream.

// For Lab 0, please replace with a real implementation that passes the
// automated checks run by `make check_lab0`.

// You will need to add private members to the class declaration in `byte_stream.hh`

template <typename... Targs>
void DUMMY_CODE(Targs &&... /* unused */) {}

using namespace std;

ByteStream::ByteStream(const size_t capacity) : _stream(capacity), _capacity(capacity), _remain_capacity(capacity), _bytes_written(0), _bytes_poped(0), _input_end(0), _eof_flag(0)
{
    _stream.clear();
}

size_t ByteStream::write(const string &data) {
    size_t byte_writen = 0;
    _input_end = 0;
    size_t remain_capacity = remaining_capacity();
    if(remain_capacity == 0){return 0;}
    for (char c : data){
        _stream.push_back(c);
        byte_writen++;
        if(byte_writen >= remain_capacity){break;}
    }
    _bytes_written += byte_writen; 
    return byte_writen;
}

//! \param[in] len bytes will be copied from the output side of the buffer
string ByteStream::peek_output(const size_t len) const {
    string sub;
    size_t stream_size = _stream.size();
    size_t i = 0;
    for(i = 0;i<len && i<stream_size;i++){
        sub.append(1,_stream.at(i));
        if(i == stream_size-1){
            
        }
    }
    return sub;
}

//! \param[in] len bytes will be removed from the output side of the buffer
void ByteStream::pop_output(const size_t len) {
    size_t stream_size = _stream.size();
    for(size_t i = 0; i < len && i < stream_size; i++){
        _stream.pop_front();
    } 
    _bytes_poped += len;
}

//! Read (i.e., copy and then pop) the next "len" bytes of the stream
//! \param[in] len bytes will be popped and returned
//! \returns a string
std::string ByteStream::read(const size_t len) {
    if(_stream.size() < len){
        _eof_flag = true;
    }else{
        _eof_flag = false;
    }

    string ret_str = peek_output(len);
    pop_output(len);
    
    _bytes_poped += len;
    return ret_str;
}

void ByteStream::end_input() {
    if(_input_end == 0){
        _input_end = 1;
    }
}

bool ByteStream::input_ended() const { return _input_end; }

size_t ByteStream::buffer_size() const { return _stream.size(); }

bool ByteStream::buffer_empty() const { return _stream.empty(); }

bool ByteStream::eof() const { 
    if(_stream.empty() && _input_end){
        return true;
    }
    return _eof_flag; 
}

size_t ByteStream::bytes_written() const { return _bytes_written; }

size_t ByteStream::bytes_read() const { return _bytes_poped; }

size_t ByteStream::remaining_capacity() const { return _capacity-_stream.size(); }
