/**
 * @file   storage_manager.h
 * @author Stavros Papadopoulos <stavrosp@csail.mit.edu>
 *
 * @section LICENSE
 *
 * The MIT License
 *
 * @copyright Copyright (c) 2015 Stavros Papadopoulos <stavrosp@csail.mit.edu>
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
 * This file defines class StorageManager.  
 */  

#ifndef __STORAGE_MANAGER_H__
#define __STORAGE_MANAGER_H__

#include "array.h"
#include "array_iterator.h"
#include "array_schema.h"
#include "array_schema_c.h"
#include "metadata.h"
#include "metadata_iterator.h"
#include "metadata_schema_c.h"
#include <string>

/* ********************************* */
/*             CONSTANTS             */
/* ********************************* */

// Return codes
#define TILEDB_SM_OK        0
#define TILEDB_SM_ERR      -1
#define TILEDB_SM_MASTER_CATALOG "master_catalog"

/** 
 * The Storage Manager is the most important module of TileDB, which is
 * repsonsible pretty much for everything.
 */
class StorageManager {
 public: 
  // TYPE DEFINITIONS

  // TODO
  enum MasterCatalogOp {TILEDB_SM_MC_INS, TILEDB_SM_MC_DEL};

  // CONSTRUCTORS & DESTRUCTORS  

  /** Constructor. */
  StorageManager();

  /** Destructor. */
  ~StorageManager();

  // TODO
  int init(const char* config_filename);

  // TODO
  int master_catalog_create() const;

  // TODO
  int create_master_catalog_entry(
      const std::string& dir, 
      MasterCatalogOp op) const;

  // WORKSPACE
  // TODO
  int ls_workspaces(
      char** workspaces,
      int& workspace_num) const;

  // TODO
  int ls(
      const char* parent_dir,
      char** dirs,
      int* dir_types,
      int& dir_num) const;

  // TODO
  int metadata_move(
       const std::string& old_dir,
       const std::string& new_dir) const;
  // TODO
  int array_move(
       const std::string& old_dir,
       const std::string& new_dir) const;
  // TODO
  int group_move(
       const std::string& old_dir,
       const std::string& new_dir) const;
  // TODO
  int workspace_move(
       const std::string& old_dir,
       const std::string& new_dir) const;

  // TODO
  int metadata_delete(const std::string& dir) const;
  // TODO
  int array_delete(const std::string& dir) const;
  // TODO
  int group_delete(const std::string& dir) const;
  // TODO
  int workspace_delete(const std::string& dir) const;

  // TODO
  int metadata_clear(const std::string& dir) const;

  // TODO
  int group_clear(const std::string& dir) const;

  // TODO
  int array_clear(const std::string& dir) const;

  // TODO
  int workspace_clear(const std::string& dir) const;

  // TODO
  int workspace_create(const std::string& dir) const; 

  // GROUP

  /**
   * Creates a new group.
   *
   * @param dir The name of the directory of the group. Note that the parent
   *      of this directory must be a TileDB workspace or group.
   * @return TILEDB_SM_OK for success, and TILEDB_SM_ERR for error.
   */
  int group_create(const std::string& dir) const; 

  // ARRAY

  /**
   * Creates an array.
   *
   * @param array_schema_c A C-style array schema object.
   * @return TILEDB_SM_OK for success, and TILEDB_SM_ERR for error.
   */
  int array_create(const ArraySchemaC* array_schema_c) const; 

  /**
   * Creates an array.
   *
   * @param array_schema A C++-style array schema object.
   * @return TILEDB_SM_OK for success, and TILEDB_SM_ERR for error.
   */
  int array_create(const ArraySchema* array_schema) const; 

  /**
   * Initializes an array object.
   *
   * @param array The array object to be initialized.
   * @param dir The directory of the array to be initialized.
   * @param mode The mode of the array. It must be one of the following:
   *    - TILEDB_WRITE 
   *    - TILEDB_WRITE_UNSORTED 
   *    - TILEDB_READ 
   *    - TILEDB_READ_REVERSE 
   * @param range The range in which the array read/write will be constrained.
   * @param attributes A subset of the array attributes the read/write will be
   *     constrained.
   * @param attribute_num The number of the input attributes.
   * @return TILEDB_SM_OK on success, and TILEDB_SM_ERR on error.
   */
  int array_init(
      Array*& array,
      const char* dir,
      int mode, 
      const void* range,
      const char** attributes,
      int attribute_num) const;

  // TODO
  int array_iterator_init(
      ArrayIterator*& array_it,
      const char* dir,
      const void* range,
      const char** attributes,
      int attribute_num,
      void** buffers,
      size_t* buffer_sizes) const;

  // TODO
  int metadata_iterator_init(
      MetadataIterator*& metadata_it,
      const char* dir,
      const char** attributes,
      int attribute_num,
      void** buffers,
      size_t* buffer_sizes) const;

  // TODO
  int metadata_init(
      Metadata*& metadata,
      const char* dir,
      int mode, 
      const char** attributes,
      int attribute_num) const;


  /** 
   * Finalizes an array. 
   *
   * @param array The array to be finalized.
   * @return TILEDB_SM_OK on success, and TILEDB_SM_ERR on error.
   */
  int array_finalize(Array* array) const;

  // TODO
  int array_iterator_finalize(ArrayIterator* array_iterator) const;

  // TODO
  int metadata_iterator_finalize(MetadataIterator* metadata_iterator) const;

  /**
   * Loads the schema of an array from the disk.
   *
   * @param dir The directory of the array.
   * @param array_schema The schema to be loaded.
   * @return TILEDB_SM_OK for success, and TILEDB_SM_ERR for error.
   */
  int array_load_schema(const char* dir, ArraySchema*& array_schema) const;

  // COMMON
  // TODO
  int clear(const std::string& dir) const;

  // TODO
  int delete_entire(const std::string& dir) const;

  // TODO
  int move(const std::string& old_dir, const std::string& new_dir) const;

  // METADATA

  // TODO
  int metadata_create(const MetadataSchemaC* metadata_schema_c) const; 

  // TODO
  int metadata_create(const ArraySchema* array_schema) const; 

  // TODO
  int metadata_load_schema(const char* dir, ArraySchema*& array_schema) const;

  // TODO
  int metadata_finalize(Metadata* array) const;

 private:
  // PRIVATE ATTRBUTES
  std::string tiledb_home_;

  // PRIVATE METHODS

  /** 
   * It sets the TileDB configuration parameters from a file.
   *
   * @param config_filename The name of the configuration file.
   *     Each line in the file correspond to a single parameter, and should
   *     be in the form <parameter> <value> (i.e., space-separated).
   * @return TILEDB_SM_OK for success, and TILEDB_SM_ERR for error.
   */
  int config_set(const char* config_filename);

  /** 
   * Sets the TileDB configuration parameters to default values. This is called
   * if config_set() fails. 
   *
   * @return void
   */
  void config_set_default();

  /**
   * Creates a special group file inside the group directory.
   *
   * @param dir The group directory.
   * @return TILEDB_SM_OK for success, and TILEDB_SM_ERR for error.
   */
  int create_group_file(const std::string& dir) const;

  // TODO
  int create_workspace_file(const std::string& dir) const;
}; 

#endif
