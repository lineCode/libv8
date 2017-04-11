//////////////////////////////////////////////////////////////////////////////////////
//
//  The MIT License (MIT)
//
//  Copyright (c) 2017-present, cyder.org
//  All rights reserved.
//
//  Permission is hereby granted, free of charge, to any person obtaining a copy of
//  this software and associated documentation files (the "Software"), to deal in the
//  Software without restriction, including without limitation the rights to use, copy,
//  modify, merge, publish, distribute, sublicense, and/or sell copies of the Software,
//  and to permit persons to whom the Software is furnished to do so, subject to the
//  following conditions:
//
//      The above copyright notice and this permission notice shall be included in all
//      copies or substantial portions of the Software.
//
//  THE SOFTWARE IS PROVIDED *AS IS*, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
//  INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
//  PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
//  HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
//  OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
//  SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
//
//////////////////////////////////////////////////////////////////////////////////////

#include "V8Console.h"
#include "../core/NativeTest.h"
#include "JSHelper.h"

namespace {

    void logMethod(const v8::FunctionCallbackInfo<v8::Value>& args) {
        v8::String::Utf8Value utf8(args[0]);
        printf("%s\n", *utf8);
    }

    void runtNativeTestMethod(const v8::FunctionCallbackInfo<v8::Value>& args) {
        auto isolate = args.GetIsolate();
        auto context = isolate->GetCurrentContext();
        auto times = static_cast<int>(args[1]->NumberValue(context).FromJust());
        auto array = v8::Local<v8::Int16Array>::Cast(args[0]);
        int size = int(array->Length() / 4);
        auto content = array->Buffer()->GetContents();
        auto data = (short*) content.Data();
        runNative(data, times, size);
    }
}

void V8Console::install(v8::Isolate* isolate, v8::Local<v8::ObjectTemplate> parent) {
    auto console = v8::ObjectTemplate::New(isolate);
    console->Set(isolate, "log", v8::FunctionTemplate::New(isolate, logMethod));
    parent->Set(isolate, "runtNativeTest",
                v8::FunctionTemplate::New(isolate, runtNativeTestMethod));
    parent->Set(isolate, "console", console);
}