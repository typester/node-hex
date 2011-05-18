#include <v8.h>
#include <node.h>
#include <node_buffer.h>

using namespace v8;
using namespace node;

static const char* hexstring = "0123456789abcdef";

static Handle<Value> Hex(const Arguments& args) {
    HandleScope scope;

    if (args.Length() != 1 || !Buffer::HasInstance(args[0]))
        return ThrowException(Exception::TypeError(String::New("Bad arguments")));

    Local<Object> buffer = args[0]->ToObject();
    char* buffer_data = Buffer::Data(buffer);
    size_t buffer_len = Buffer::Length(buffer);

    char data[buffer_len];

    int p = 0;
    for (int i = 0; i < buffer_len; ++i) {
        data[p++] = hexstring[ buffer_data[i] >> 4 ];
        data[p++] = hexstring[ buffer_data[i] & 0xf ];
    }

    Local<String> hex = String::New(data, p);

    return scope.Close(hex);
}

extern "C" void init (Handle<Object> target) {
    HandleScope scope;
    target->Set(String::NewSymbol("hex"),
        FunctionTemplate::New(Hex)->GetFunction());
}
