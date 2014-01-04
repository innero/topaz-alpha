#ifndef TOPAZ_DATUM_H
#define TOPAZ_DATUM_H

/**
 * File:   $URL $
 * Author: $Author $
 * Date:   $Date $
 * Rev:    $Revision $
 *
 * Topaz - Datum
 *
 * This class implements a TCG Opal Data Item, that is a higher level, possibly
 * aggregate data type. This includes basic atom types (integers and binary),
 * but also more complex aggregate types such as named types (key/value), lists,
 * and method calls.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#include <topaz/atom.h>
#include <topaz/encodable.h>

namespace topaz
{
  
  class datum : public encodable
  {
    
  public:
    
    // Enumeration of various datum types
    typedef enum
    {
      ATOM,       // Binary or integer type
      NAMED,      // Key / Value pair
      LIST,       // List (possibly empty)
      METHOD,     // Method call
      END_SESSION // End of session indicator
    } type_t;
    
    // Enumerations of data stream tokens
    typedef enum
    {
      // Sequence Tokens
      TOK_START_LIST  = 0xf0,
      TOK_END_LIST    = 0xf1,
      TOK_START_NAME  = 0xf2,
      TOK_END_NAME    = 0xf3,
      
      // Control Tokens
      TOK_CALL        = 0xf8,
      TOK_END_OF_DATA = 0xf9,
      TOK_END_SESSION = 0xfa,
      TOK_START_TRANS = 0xfb,
      TOK_END_TRANS   = 0xfc,
    } token_t;
    
    /**
     * \brief Default Constructor
     */
    datum();
    
    /**
     * \brief Token Constructor
     */
    datum(datum::type_t type);
    
    /**
     * \brief Atom Constructor
     */
    datum(atom const &value);
    
    /**
     * \brief Named Constructor
     */
    datum(atom const &name, atom const &value);
    
    /**
     * \brief List Constructor
     */
    datum(datum_vector const &list);
    
    /**
     * \brief Method Constructor
     */
    datum(uint64_t object_uid, uint64_t method_uid, datum_vector const &args);
    
    /**
     * \brief Destructor
     */
    ~datum();
    
    /**
     * \brief Equality Operator
     *
     * @return True when equal
     */
    bool operator==(datum const &ref);
    
    /**
     * \brief Inequality Operator
     *
     * @return True when not equal
     */
    bool operator!=(datum const &ref);
    
    /**
     * \brief Query encoded size
     *
     * @return Byte count of object when encoded
     */
    virtual size_t size() const;
    
    /**
     * \brief Encode to data buffer
     *
     * @param data Data buffer of at least size() bytes
     * @return Number of bytes encoded
     */
    virtual size_t encode_bytes(byte *data) const;
    
    /**
     * \brief Decode from data buffer
     *
     * @param data Location to read encoded bytes
     * @param len  Length of buffer
     * @return Number of bytes processed
     */
    virtual size_t decode_bytes(byte const *data, size_t len);
    
    /**
     * \brief Query Datum Type
     */
    datum::type_t get_type() const;

    /**
     * \brief Query Name
     */
    atom const &get_name() const;
    
    /**
     * \brief Query Value
     */
    atom const &get_value() const;
    
    /**
     * \brief Query Method's Object UID
     */
    uint64_t get_object_uid() const;
    
    /**
     * \brief Query Value Method UID
     */
    uint64_t get_method_uid() const;
    
    /**
     * \brief Query List
     */
    datum_vector const &get_list() const;
    
  protected:
    
    /**
     * \brief Ensure data to be decoded is of minimum size
     *
     * @param len Length of buffer
     * @param min Minimum size required for buffer
     */
    void decode_check_size(size_t len, size_t min) const;
    
    /**
     * \brief Verify next token exists and is expected value
     *
     * @param data Location to read encoded bytes
     * @param len  Length of buffer
     * @param idx  Next index
     * @param next Expected value at index
     */
    void decode_check_token(byte const *data, size_t len, size_t idx, byte next) const;
    
    // What sort of object
    datum::type_t data_type;
    
    // Atom storage
    atom name;           // Valid only on named object
    atom value;
    
    // Method call specific parameters
    uint64_t object_uid; // Object reference
    uint64_t method_uid; // Method reference
    
    // Storage of other datums (lists / method calls)
    datum_vector list;
    
  };
  
};

#endif
