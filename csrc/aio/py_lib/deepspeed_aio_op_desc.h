// Copyright (c) Microsoft Corporation.
// SPDX-License-Identifier: Apache-2.0

// DeepSpeed Team

#ifndef _IO_OP_DESC_T_
#define _IO_OP_DESC_T_
#include <memory>
#include <queue>
#include "deepspeed_py_aio.h"

struct io_op_desc_t {
    const bool _read_op;
    torch::Tensor _buffer;
    const bool _is_managed;
    int _fd;
    const std::string _filename;
    const long long int _file_num_bytes;
    const int _intra_op_parallelism;
    const long long int _num_bytes_per_thread;
    torch::Tensor _contiguous_buffer;
    const bool _validate;

    io_op_desc_t(const bool read_op,
                 const torch::Tensor& buffer,
                 const bool is_managed,
                 const int fd,
                 const char* filename,
                 const long long int file_num_bytes,
                 const int intra_op_parallelism,
                 const bool validate);

    virtual void run(const int tid,
                     std::unique_ptr<aio_context>& aio_ctxt,
                     deepspeed_aio_config_t* aio_config);

    virtual char* data_ptr() const;

    virtual void validate();

    virtual void finish();
};
#endif  // _IO_OP_DESC_T_
