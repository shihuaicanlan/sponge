#include "stream_reassembler.hh"
// Dummy implementation of a stream reassembler.

// For Lab 1, please replace with a real implementation that passes the
// automated checks run by `make check_lab1`.

// You will need to add private members to the class declaration in `stream_reassembler.hh`

template <typename... Targs>
void DUMMY_CODE(Targs &&... /* unused */) {}

using namespace std;

StreamReassembler::StreamReassembler(const size_t capacity)
    : _output(capacity)
    , _capacity(capacity)
    , predict_index(0)
    , unassembled_cnt(0)
    , datastream()
    , charf(capacity)
    , _eof(false) {}

//! \details This function accepts a substring (aka a segment) of bytes,
//! possibly out-of-order, from the logical stream, and assembles any newly
//! contiguous substrings and writes them into the output stream in order.
void StreamReassembler::push_substring(const string &data, const size_t index, const bool eof) {
    //字符串的最大索引
    size_t len = predict_index + _output.remaining_capacity();
    size_t r = index + data.size();  // data的右边界
    if (eof == true && r <= len)
        _eof = true;
    if (index >= len)
        return;
    if (r > predict_index) {
        //将多余的部分装入
        for (auto i = max(index, predict_index); i < min(r, len); i++) {
            //新数据没放入过
            if (charf.count(i) == 0) {
                //动态扩容
                if (datastream.size()<= i) {
                    datastream.resize(2*i+1);
                }
                datastream[i] = data.at(i - index);
                charf.insert(i);
                unassembled_cnt++;
            }
        }
        std::string tempstr = "";
        //更新predict_index并且将连续的writer
        while (charf.count(predict_index) > 0) {
            tempstr += datastream[predict_index];
            charf.erase(predict_index);
            predict_index++;
            unassembled_cnt--;
        }
        if (tempstr != "") {
            _output.write(tempstr);
        }
    }
    if (_eof && empty()) {
        _output.end_input();
    }
}

size_t StreamReassembler::unassembled_bytes() const { return unassembled_cnt; }

bool StreamReassembler::empty() const { return unassembled_cnt == 0; }
