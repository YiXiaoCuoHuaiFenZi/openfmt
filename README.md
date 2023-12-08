## openfmt

Open source code format tool for Protobuf.

## Usage

```shell
****************************************************************************************************
*                                     Protobuf file formatter                                      *
*                                           MIT License                                            *
****************************************************************************************************
usage:
  openfmt -f [filepath] or -d [file_folder] [option=<value>]

mandatory:
  -f                           single file model, format the specified proto file.
  -d                           folder model, will format proto files under the specified folder and
                               all sub-folders.
options:
  --preview                    preview formatted protobuf file(s) with syntax highlighting in
                               terminal or command line window. choices: [true, false], default
                               value is false, if it set to true, protobuf file(s) will not be
                               overwritten by formatted one(s).
  --indents                    the number of indented spaces, default is 4.
  --top-comment                convert single line comment at the right of the code line to top
                               comment(above the code line), choices: [true, false], default value
                               is false.
  --align-by-equal-sign        align the code by equal sign. choices: [true, false], default
                               is true.
version:
  -v                           show current version of openfmt.
  --version                    show current version of openfmt.
help:
  -h                           show this help message and exit.
  --help                       show this help message and exit.
```

## Example

Before format:

```protobuf
// test multiple empty lines at the end of proto file.

syntax = "proto3";
package dasdsadsd;
option java_package = "ba.la.ba.la";
option objc_class_prefix = "dasdas";

    /*
    **    The RFIC (Reason for Issuance Code) is the group of services the EMD belongs to.
     **    Examples: A => Air Transportation, C => Baggage and G => In-flight services.
    **    All fare baggage these 2 passengers can take is 2  2 = 4
    **    <PaymentCardCharacteristics xmlns="http://ndc.google.net">
    **    This is a single character code indicating the reason for issuance.
    **    Examples: A => Air Transportation, C => Baggage and G => In-flight services.
    */
import "base.proto";

//Linear measurement = length + width + height
// TestOuter
message TestOuter {string header = 1;message TestInner {string header = 1;// TestInner header
  string market = 2; // TestInner market
  // TestInner message inner bottom
  //TestInner message inner bottom bottombottombottombottom
}
  // market
  //market marketmarketmarket
  string market = 2; // market
  // TestOuter message inner bottom
  //TestOuter message inner bottom bottombottombottombottom
}
//proto bottom
//proto bottom bottombottombottombottom
```

After format:

```protobuf
/*
**    test multiple empty lines at the end of proto file.
*/
syntax = "proto3";

package dasdsadsd;

option java_package      = "ba.la.ba.la";
option objc_class_prefix = "dasdas";

/*
**    The RFIC (Reason for Issuance Code) is the group of services the EMD belongs to.
**    Examples: A => Air Transportation, C => Baggage and G => In-flight services.
**    All fare baggage these 2 passengers can take is 2  2 = 4
**    <PaymentCardCharacteristics xmlns="http://ndc.google.net">
**    This is a single character code indicating the reason for issuance.
**    Examples: A => Air Transportation, C => Baggage and G => In-flight services.
*/
import "base.proto";

/*
**    Linear measurement = length + width + height
**    TestOuter
*/
message TestOuter {
    string header = 1;
    message TestInner {
        string header = 1;  // TestInner header
        string market = 2;  // TestInner market
        /*
        **    TestInner message inner bottomTestInner message inner bottom
        **    TestInner message inner bottom bottombottombottombottomTestInner message inner bottom bottombottombottombottom
        */
    }
    /*
    **    market
    **    market marketmarketmarket
    */
    string market = 2;  // market
    /*
    **    TestOuter message inner bottomTestOuter message inner bottom
    **    TestOuter message inner bottom bottombottombottombottomTestOuter message inner bottom bottombottombottombottom
    */
}
/*
**    proto bottom
**    proto bottom bottombottombottombottom
*/

```