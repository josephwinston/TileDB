
/**
 * @file   unit-capi-error.cc
 *
 * @section LICENSE
 *
 * The MIT License
 *
 * @copyright Copyright (c) 2017 TileDB Inc.
 * @copyright Copyright (c) 2016 MIT and Intel Corporation
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 * @section DESCRIPTION
 *
 * Tests for the C API error return code
 */

#include "tiledb.h"

#include "catch.hpp"

TEST_CASE("C API Error") {
  TileDB_CTX* ctx;
  int rc;
  rc = tiledb_ctx_init(&ctx, nullptr);
  CHECK(rc == TILEDB_OK);

  const char* bad_path = nullptr;
  rc = tiledb_clear(ctx, bad_path);
  CHECK(rc == TILEDB_ERR);

  tiledb_error_t* err = tiledb_error_last(ctx);
  CHECK_THAT(
      tiledb_error_message(err),
      Catch::Equals("Error: Invalid directory argument is NULL"));
  tiledb_error_free(err);
}