/*
 *  Copyright 2008-2009 NVIDIA Corporation
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 */


/*! \file vectorize.h
 *  \brief Defines the interface for a function that executes a 
 *  function or functional for each value in [0,n)
 */

#pragma once

namespace komrade
{

namespace detail
{

namespace device
{

namespace cuda
{


template<typename IndexType,
         typename UnaryFunction>
void vectorize(IndexType n, UnaryFunction f);


} // end namespace cuda

} // end namespace device

} // end namespace detail

} // end namespace komrade

#include <komrade/detail/device/cuda/vectorize.inl>

