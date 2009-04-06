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


/*! \file copy.h
 *  \brief Defines the interface to copy between containers.
 */

#pragma once

#include <komrade/detail/config.h>

namespace komrade
{
	
/*! \addtogroup algorithms
 */

/*! \addtogroup copying
 *  \ingroup algorithms
 *  \{
 */
	
/*! \addtogroup regular_copying Regular Copying
 *  \ingroup copying
 *  \{
 */

/*! \p copy copies elements from the range [\p first, \p last) to the range
 *  [\p result, \p result + (\p last - \p first)). That is, it performs
 *  the assignments *\p result = *\p first, *(\p result + \c 1) = *(\p first + \c 1),
 *  and so on. Generally, for every integer \c n from \c 0 to \p last - \p first, \p copy
 *  performs the assignment *(\p result + \c n) = *(\p first + \c n). Unlike
 *  \c std::copy, \p copy offers no guarantee on order of operation.
 *
 *  The return value is \p result + (\p last - \p first).
 *
 *  \param first The beginning of the sequence to copy.
 *  \param last The end of the sequence to copy.
 *  \param result The destination sequence.
 *  \return The end of the destination sequence.
 *  \see http://www.sgi.com/tech/stl/copy.html
 *
 *  \tparam InputIterator must be a model of <a href="http://www.sgi.com/tech/stl/InputIterator.html">Input Iterator</a> and \c InputIterator's \c value_type must be convertible to \c OutputIterator's \c value_type.
 *  \tparam OutputIterator must be a model of <a href="http://www.sgi.com/tech/stl/OutputIterator.html">Output Iterator</a>.
 *
 *  The following code snippet demonstrates how to use \p copy
 *  to copy from one range to another.
 *
 *  \code
 *  #include <komrade/copy.h>
 *  #include <komrade/device_vector.h>
 *  ...
 *
 *  komrade::device_vector<int> vec0(100);
 *  komrade::device_vector<int> vec1(100);
 *  ...
 *
 *  komrade::copy(vec0.begin(), vec0.end(),
 *                vec1.begin());
 *
 *  // vec1 now contains the contents of vec0
 *  \endcode
 */
template<typename InputIterator, typename OutputIterator>
  OutputIterator copy(InputIterator first,
                      InputIterator last,
                      OutputIterator result);

/*! \p copy_if conditionally copies elements from the range [\p first, \p last)
 *  to the range [\p result, \p result + (\p last - \p first)). For each iterator
 *  \c i in the range [\p first, \p last) such that *(\p stencil + (\c i - \p first))
 *  is \c true, the value *\c i is assigned to *(\p result + \c i). Otherwise,
 *  *(\p result + \c i) is left unchanged.
 *
 *  The return value is \p result + (\p last - \p first).
 *
 *  \param first The beginning of the sequence to copy.
 *  \param last The end of the sequence to copy.
 *  \param stencil Predicate iterator controlling the copy.
 *  \param result The destination sequence.
 *  \return The end of the destination sequence.
 *
 *  \tparam InputIterator must be a model of <a href="http://www.sgi.com/tech/stl/InputIterator.html">Input Iterator</a> and \c InputIterator's \c value_type must be convertible to \c OutputIterator's \c value_type.
 *  \tparam PredicateIterator must be a model of <a href="http://www.sgi.com/tech/stl/InputIterator.html">Input Iterator</a> and \c value_type must be convertible to \c bool.
 *  \tparam OutputIterator must be a model of <a href="http://www.sgi.com/tech/stl/OutputIterator.html">Output Iterator</a>.
 *
 *  The following code snippet demonstrates how to use \p copy_if to
 *  copy every other element from an input range to an output range.
 *
 *  \code
 *  #include <komrade/copy.h>
 *  #include <komrade/device_vector.h>
 *  ...
 *  int   input[10] = {0, 2, 3, 4, 5, 6, 7, 8, 9};
 *  int stencil[10] = {1, 0, 1, 0, 1, 0, 1, 0, 1};
 *  komrade::device_vector<int> output(10,0);
 *  ...
 *  komrade::copy_if(input, input + 10,
 *                   stencil,
 *                   output.begin());
 *  // every other element of output is now equal to
 *  // every other element of input
 *  \endcode
 */
template<typename InputIterator,
         typename PredicateIterator,
         typename OutputIterator>
  OutputIterator copy_if(InputIterator first,
                         InputIterator last,
                         PredicateIterator stencil,
                         OutputIterator result);

/*! \p copy_if conditionally copies elements from the range [\p first, \p last)
 *  to the range [\p result, \p result + (\p last - \p first)). For each iterator
 *  \c i in [\p first, \p last) such that \p pred(*(\p stencil + (\c i - \p last))) is
 *  \p true, the value *\c i is assigned to *(\p result + \c i). Otherwise,
 *  *(\p result + \c i) is left unchanged.
 *
 *  The return value is \p result + (\p last - \p first).
 *
 *  \param begin The beginning of the sequence to copy.
 *  \param end The end of the sequence to copy.
 *  \param stencil Predicate iterator controlling the copy.
 *  \param result The destination sequence.
 *  \param pred Predicate used on stencil values.
 *  \return The end of the destination sequence.
 *
 *  \tparam InputIterator must be a model of <a href="http://www.sgi.com/tech/stl/InputIterator.html">Input Iterator</a> and \c InputIterator's \c value_type must be convertible to \c OutputIterator's \c value_type.
 *  \tparam PredicateIterator must be a model of <a href="http://www.sgi.com/tech/stl/InputIterator.html">Input Iterator</a> and \c PredicateIterator's \c value_type must be convertible to \c Predicate's \c argument_type. 
 *  \tparam OutputIterator must be a model of <a href="http://www.sgi.com/tech/stl/OutputIterator.html">Output Iterator</a>.
 *  \tparam Predicate must be a model of <a href="http://www.sgi.com/tech/stl/Predicate.html">Predicate</a>.
 *
 *  The following code snippet demonstrates how to use \p copy_if to
 *  copy odd elements from an input range to an output range.
 *
 *  \code
 *  #include <komrade/copy.h>
 *  #include <komrade/device_vector.h>
 *  ...
 *  struct is_odd
 *  {
 *    __host__ __device__
 *    bool operator()(const int &x)
 *    {
 *      return x & 1;
 *    }
 *  };
 *  ...
 *  komrade::device_vector<int> input(10);
 *  komrade::device_vector<int> output(10);
 *  ...
 *  // fill input
 *  ...
 *  komrade::copy_if(input.begin(), input.end(),
 *                   input.begin(),
 *                   output.begin(),
 *                   is_odd());
 *  // odd elements of input have been copied to output
 *  \endcode
 */
template<typename InputIterator,
         typename PredicateIterator,
         typename OutputIterator,
         typename Predicate>
  OutputIterator copy_if(InputIterator begin,
                         InputIterator end,
                         PredicateIterator stencil,
                         OutputIterator result,
                         Predicate pred);

/*! \} // end regular_copying
 */

/*! \} // end copying
 */
	
} // end namespace komrade

#include <komrade/detail/copy.inl>

