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


/*! \file device_delete.h
 *  \brief Defines the interface to a wrapper for cudaFree.
 */

#pragma once

#include <komrade/detail/config.h>
#include <komrade/device_ptr.h>

namespace komrade
{

/*! \addtogroup deallocation_functions Deallocation Functions
 *  \ingroup memory_management_functions
 *  \{
 */

/*! \p device_delete deletes a \p device_ptr allocated with
 *  \p device_new.
 *
 *  \param ptr The \p device_ptr to delete, assumed to have
 *         been allocated with \p device_new.
 *
 *  \bug The current implementation of \p device_delete does
 *  not invoke <tt>T</tt>'s destructor on the object <tt>*ptr</tt>.
 *
 *  \see device_ptr
 *  \see device_new
 */
template<typename T>
  inline void device_delete(komrade::device_ptr<T> ptr);

/*! \}
 */

} // end komrade

#include <komrade/detail/device_delete.inl>

