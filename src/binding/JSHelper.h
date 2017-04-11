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


#ifndef HELLOV8_JSHELPER_H
#define HELLOV8_JSHELPER_H

#include <v8.h>


#define JSString(text) v8::String::NewFromUtf8(isolate, text, v8::NewStringType::kNormal).ToLocalChecked()
#define JSFunction(callback) v8::Function::New(context,callback).ToLocalChecked()

#define GETTER_ARGUMENT v8::Local<v8::Name> property, const v8::PropertyCallbackInfo<v8::Value>& info

#define GETTER_CONTENT(className, name) \
    auto self = info.Holder(); \
    auto ptr = self->GetAlignedPointerFromInternalField(0); \
    auto value = static_cast<className*>(ptr)->name; \
    info.GetReturnValue().Set(value);

#define SETTER_ARGUMENT v8::Local<v8::Name> property, v8::Local<v8::Value> value, const v8::PropertyCallbackInfo<void>& info

#define SETTER_CONTENT(className, name) \
    auto self = info.Holder(); \
    auto isolate = info.GetIsolate(); \
    auto context = isolate->GetCurrentContext(); \
    auto ptr = self->GetAlignedPointerFromInternalField(0); \
    static_cast<className*>(ptr)->name = (float) value->NumberValue(context).FromJust();

#define SET_ACCESSOR(name, getter, setter) self->SetAccessor(context, JSString(name), getter, setter);

#define SET_METHOD(name, method) prototypeTemplate->Set(isolate, name, \
                                                            v8::FunctionTemplate::New(isolate, method));


#endif //HELLOV8_JSHELPER_H
