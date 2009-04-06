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


/*! \file device_malloc.inl
 *  \brief Inline file for device_malloc.h.
 */

#include <komrade/device_malloc.h>
#include <komrade/detail/device/cuda/malloc.h>

namespace komrade
{

komrade::device_ptr<void> device_malloc(const std::size_t n)
{
  return detail::device::cuda::malloc(n);
} // end device_malloc()

template<typename T>
  komrade::device_ptr<T> device_malloc(const std::size_t n)
{
  return komrade::device_malloc(n * sizeof(T));
} // end device_malloc()

} // end komrade

