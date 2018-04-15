# libimages

Interface which reads, processes and writes images with multithreading.

# Depends

- [OpenCV](https://github.com/opencv/opencv)
- [libexstl](https://github.com/centixkadon/libexstl)

# Build

```shell
cd .
git clone https://github.com/centixkadon/libexstl.git
git clone https://github.com/centixkadon/libimages.git
mkdir build && cd build
cmake ../libimages/test
make
```

# Usage

Inherit the class **Images** and implement the interface **calculate** and **evaluate**,
as is shown in the test module.
