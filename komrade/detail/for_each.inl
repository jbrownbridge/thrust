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


/*! \file for_each.inl
 *  \brief Inline file for for_each.h.
 */

#include <komrade/for_each.h>
#include <komrade/iterator/iterator_traits.h>
#include <komrade/detail/dispatch/for_each.h>

namespace komrade
{

/////////////////
// Entry Point //
/////////////////
template<typename InputIterator,
         typename UnaryFunction>
void for_each(InputIterator first,
              InputIterator last,
              UnaryFunction f)
{
  // dispatch on iterator_category
  komrade::detail::dispatch::for_each(first, last, f,
          typename komrade::iterator_traits<InputIterator>::iterator_category());
} // end for_each()

} // end namespace komrade

