#include "tcp_receiver.hh"

#include "wrapping_integers.hh"

#include <cstdint>
#include <optional>

// Dummy implementation of a TCP receiver

// For Lab 2, please replace with a real implementation that passes the
// automated checks run by `make check_lab2`.

template <typename... Targs>
void DUMMY_CODE(Targs &&.../* unused */) {}

using namespace std;

void TCPReceiver::segment_received(const TCPSegment &seg) {
   //连接阶段
    if (seg.header().syn && is_syn == false) {
        is_syn = true;
        isn_cnt = seg.header().seqno;
        _reassembler.push_substring(seg.payload().copy(), 0, seg.header().fin);//第一次连接发送的str_index一定=0
    } else if (is_syn == false) //监听阶段
        return;
    //发送阶段
    uint64_t str_index =
        unwrap(seg.header().seqno, isn_cnt, static_cast<uint64_t>(_reassembler.stream_out().bytes_written()));
    if (str_index != 0) {
        _reassembler.push_substring(seg.payload().copy(), str_index - 1, seg.header().fin);
    }
}

optional<WrappingInt32> TCPReceiver::ackno() const {
    if (!is_syn) {
        return nullopt;
    }
    uint64_t res = _reassembler.stream_out().bytes_written() + 1;
    if (_reassembler.stream_out().input_ended())
        res++;
    return wrap(res, isn_cnt);
}

size_t TCPReceiver::window_size() const { return _reassembler.stream_out().remaining_capacity(); }
