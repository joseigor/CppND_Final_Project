
/*
 * This file was automatically generated by sdbus-c++-xml2cpp; DO NOT EDIT!
 */

#ifndef __sdbuscpp__IComCppndCalculator_hpp__adaptor__H__
#define __sdbuscpp__IComCppndCalculator_hpp__adaptor__H__

#include <sdbus-c++/sdbus-c++.h>
#include <string>
#include <tuple>

namespace com {
namespace cppnd {

class calculator_adaptor
{
public:
    static constexpr const char* INTERFACE_NAME = "com.cppnd.calculator";

protected:
    calculator_adaptor(sdbus::IObject& object)
        : object_(object)
    {
        object_.registerMethod("Add").onInterface(INTERFACE_NAME).withInputParamNames("values").withOutputParamNames("result").implementedAs([this](const std::vector<double>& values){ return this->Add(values); });
        object_.registerMethod("Sub").onInterface(INTERFACE_NAME).withInputParamNames("a", "b").withOutputParamNames("result").implementedAs([this](const double& a, const double& b){ return this->Sub(a, b); });
        object_.registerMethod("Mult").onInterface(INTERFACE_NAME).withInputParamNames("values").withOutputParamNames("result").implementedAs([this](const std::vector<double>& values){ return this->Mult(values); });
        object_.registerMethod("Div").onInterface(INTERFACE_NAME).withInputParamNames("a", "b").withOutputParamNames("result").implementedAs([this](const double& a, const double& b){ return this->Div(a, b); });
    }

    ~calculator_adaptor() = default;

private:
    virtual double Add(const std::vector<double>& values) = 0;
    virtual double Sub(const double& a, const double& b) = 0;
    virtual double Mult(const std::vector<double>& values) = 0;
    virtual double Div(const double& a, const double& b) = 0;

private:
    sdbus::IObject& object_;
};

}} // namespaces

#endif