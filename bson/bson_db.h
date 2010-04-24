/** @file bson_db.h 

    This file contains the implementation of BSON-related methods that are required 
    by the MongoDB database server.

    Normally, for standalone BSON usage, you do not want this file - it will tend to 
    pull in some other files from the MongoDB project. Thus, bson.h (the main file 
    one would use) does not include this file.
*/

/*    Copyright 2009 10gen Inc.
 *
 *    Licensed under the Apache License, Version 2.0 (the "License");
 *    you may not use this file except in compliance with the License.
 *    You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 *    Unless required by applicable law or agreed to in writing, software
 *    distributed under the License is distributed on an "AS IS" BASIS,
 *    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *    See the License for the specific language governing permissions and
 *    limitations under the License.
 */

#pragma once

#include "../util/optime.h"

namespace mongo {

    inline OpTime BSONElement::_opTime() const {
        return OpTime( *reinterpret_cast< const unsigned long long* >( value() ) );
    }

    inline string BSONElement::_asCode() const {
        switch( type() ){
        case mongo::String:
        case Code:
            return valuestr();
        case CodeWScope:
            return codeWScopeCode();
        default:
            log() << "can't convert type: " << (int)(type()) << " to code" << endl;
        }
        uassert( 10062 ,  "not code" , 0 );
        return "";
    }

}
