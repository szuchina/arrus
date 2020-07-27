#ifndef ARRUS_API_MATLAB_WRAPPERS_ARRUS_SESSIONOBJECTWRAPPER_H
#define ARRUS_API_MATLAB_WRAPPERS_ARRUS_SESSIONOBJECTWRAPPER_H

#include <utility>

#include "api/matlab/wrappers/MexObjectWrapper.h"
#include "api/matlab/wrappers/DefaultMexObjectManager.h"
#include "core/session/Session.h"

namespace arrus::matlab_wrappers {


class SessionWrapper : public MexObjectWrapper {
public:

    explicit SessionWrapper(
            std::shared_ptr<MexContext> ctx,
            const MexMethodArgs &args)
            : MexObjectWrapper(std::move(ctx)) {
        this->ctx->logInfo("Constructor");
        this->addMethod("test1", std::bind(&SessionWrapper::test1,
                this, std::placeholders::_1));
        this->addMethod("test2", std::bind(&SessionWrapper::test2,
                this, std::placeholders::_1));
    }

    ~SessionWrapper() override {
        ctx->logInfo("Destructor");
    }

    MexMethodReturnType test1(const MexMethodArgs &inputs) {
        return ctx->getArrayFactory().createCellArray({0});
    }

    MexMethodReturnType test2(const MexMethodArgs &inputs) {
        return ctx->getArrayFactory().createCellArray({1, 2},
                "abc",
                ctx->getArrayFactory().createArray<double>({2, 2}, {1., 2., 3., 4.}));
    }
};

class SessionWrapperManager : public DefaultMexObjectManager<SessionWrapper> {
    using DefaultMexObjectManager::DefaultMexObjectManager;
};

}

#endif
