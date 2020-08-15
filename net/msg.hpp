#include <stdint.h>
#include <string>
#include <memory>
#include <google/protobuf/message.h>
/*
    uint32_t len;
    uint32_t msg_type;
    std::string content;
*/
enum{
    MSG_START = 0x00000000,
    MSG_PING = 0x00000001,
    MSG_PONG = 0x00000002,
};
class Msg{
public:
    std::string static EncodeProtobuf2String(std::shared_ptr<::google::protobuf::Message> msg);
    std::shared_ptr<::google::protobuf::Message> static DecodeString2Protobuf(std::string& msg);
    uint32_t static GetMsgType(const std::string& msg_type);
    std::string static GetMsgType(uint32_t msg_type);
};