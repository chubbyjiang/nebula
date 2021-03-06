/* Copyright (c) 2018 vesoft inc. All rights reserved.
 *
 * This source code is licensed under Apache 2.0 License,
 * attached with Common Clause Condition 1.0, found in the LICENSES directory.
 */

#ifndef GRAPH_EXECUTIONCONTEXT_H_
#define GRAPH_EXECUTIONCONTEXT_H_

#include "base/Base.h"
#include "cpp/helpers.h"
#include "graph/RequestContext.h"
#include "parser/SequentialSentences.h"
#include "meta/SchemaManager.h"
#include "graph/VariableHolder.h"
#include "meta/client/MetaClient.h"

/**
 * ExecutionContext holds context infos in the execution process, e.g. clients of storage or meta services.
 */

namespace nebula {
namespace storage {
class StorageClient;
}   // namespace storage
namespace graph {

class ExecutionContext final : public cpp::NonCopyable, public cpp::NonMovable {
public:
    using RequestContextPtr = std::unique_ptr<RequestContext<cpp2::ExecutionResponse>>;
    ExecutionContext(RequestContextPtr rctx,
                     meta::SchemaManager *sm,
                     storage::StorageClient *storage,
                     meta::MetaClient *metaClient) {
        rctx_ = std::move(rctx);
        sm_ = sm;
        storage_ = storage;
        metaClient_ = metaClient;
        variableHolder_ = std::make_unique<VariableHolder>();
    }

    ~ExecutionContext();

    RequestContext<cpp2::ExecutionResponse>* rctx() const {
        return rctx_.get();
    }

    meta::SchemaManager* schemaManager() const {
        return sm_;
    }

    storage::StorageClient* storage() const {
        return storage_;
    }

    VariableHolder* variableHolder() const {
        return variableHolder_.get();
    }

    meta::MetaClient* getMetaClient() const {
        return metaClient_;
    }

private:
    RequestContextPtr                           rctx_;
    meta::SchemaManager                        *sm_{nullptr};
    storage::StorageClient                     *storage_{nullptr};
    meta::MetaClient                           *metaClient_{nullptr};
    std::unique_ptr<VariableHolder>             variableHolder_;
};

}   // namespace graph
}   // namespace nebula

#endif  // GRAPH_EXECUTIONCONTEXT_H_
