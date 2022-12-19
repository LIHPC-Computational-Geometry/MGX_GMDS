# MGX_GMDS

Previous version of GMDS. It is deprecated and only used right now for MGX.


Temporary version that must be removed. Up to now, it can be 
installed using the github workflow as a documentation. Otherwise
the procedure is the next one:

```sh
git clone git@github.com:LIHPC-Computational-Geometry/MGX_GMDS.git
mkdir build
cd build
cmake ../MGX_GMDS/ -DCMAKE_INSTALL_PREFIX=install 
cmake ../MGX_GMDS/test_link/ -DCMAKE_PREFIX_PATH=$(absolute_path)/install
./test_link
```