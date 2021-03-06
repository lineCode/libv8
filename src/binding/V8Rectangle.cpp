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

#include "V8Rectangle.h"
#include "../core/Rectangle.h"
#include "JSHelper.h"

namespace {

    void xGetter(GETTER_ARGUMENT) { GETTER_CONTENT(Rectangle, x); }

    void xSetter(SETTER_ARGUMENT) { SETTER_CONTENT(Rectangle, x); }

    void yGetter(GETTER_ARGUMENT) { GETTER_CONTENT(Rectangle, y); }

    void ySetter(SETTER_ARGUMENT) { SETTER_CONTENT(Rectangle, y); }

    void widthGetter(GETTER_ARGUMENT) { GETTER_CONTENT(Rectangle, width); }

    void widthSetter(SETTER_ARGUMENT) { SETTER_CONTENT(Rectangle, width); }

    void heightGetter(GETTER_ARGUMENT) { GETTER_CONTENT(Rectangle, height); }

    void heightSetter(SETTER_ARGUMENT) { SETTER_CONTENT(Rectangle, height); }


    void setToMethod(const v8::FunctionCallbackInfo<v8::Value>& args) {
        auto isolate = args.GetIsolate();
        auto context = isolate->GetCurrentContext();
        float x = float(args[0]->IsUndefined() ? 0 : args[0]->NumberValue(context).FromJust());
        float y = float(args[1]->IsUndefined() ? 0 : args[1]->NumberValue(context).FromJust());
        float width = float(args[2]->IsUndefined() ? 0 : args[2]->NumberValue(context).FromJust());
        float height = float(args[3]->IsUndefined() ? 0 : args[3]->NumberValue(context).FromJust());
        auto self = args.Holder();
        auto ptr = self->GetAlignedPointerFromInternalField(0);
        static_cast<Rectangle*>(ptr)->setTo(x, y, width, height);
    }

    void toStringMethod(const v8::FunctionCallbackInfo<v8::Value>& args) {
        auto self = args.Holder();
        auto isolate = args.GetIsolate();
        auto rect = static_cast<Rectangle*>(self->GetAlignedPointerFromInternalField(0));
        auto value = rect->toString();
        auto utf = JSString(value.c_str());
        args.GetReturnValue().Set(utf);
    }

    void constructor(const v8::FunctionCallbackInfo<v8::Value>& args) {
        auto isolate = args.GetIsolate();
        auto context = isolate->GetCurrentContext();
        float x = float(args[0]->IsUndefined() ? 0 : args[0]->NumberValue(context).FromJust());
        float y = float(args[1]->IsUndefined() ? 0 : args[1]->NumberValue(context).FromJust());
        float width = float(args[2]->IsUndefined() ? 0 : args[2]->NumberValue(context).FromJust());
        float height = float(args[3]->IsUndefined() ? 0 : args[3]->NumberValue(context).FromJust());
        Rectangle* rect = new Rectangle(x, y, width, height);
        auto self = args.Holder();
        self->SetAlignedPointerInInternalField(0, rect);
        SET_ACCESSOR("x", xGetter, xSetter);
        SET_ACCESSOR("y", yGetter, ySetter);
        SET_ACCESSOR("width", widthGetter, widthSetter);
        SET_ACCESSOR("height", heightGetter, heightSetter);
        args.GetReturnValue().Set(self);
    }


}

void V8Rectangle::install(v8::Isolate* isolate, v8::Local<v8::ObjectTemplate> parent) {
    auto classTemplate = v8::FunctionTemplate::New(isolate, constructor);
    classTemplate->SetClassName(JSString("Rectangle"));
    auto prototypeTemplate = classTemplate->PrototypeTemplate();
    SET_METHOD("setTo", setToMethod);
    SET_METHOD("toString", toStringMethod);
    classTemplate->InstanceTemplate()->SetInternalFieldCount(1);

    parent->Set(JSString("Rectangle"), classTemplate);
}
