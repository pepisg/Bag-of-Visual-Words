# Bag of Visual Words

This repository contains my solution to the final project on the modern C++ [course](https://www.youtube.com/playlist?list=PLgnQpQtFTOGRM59sr3nSL8BmeMZR9GCIA) made by [Cyrill Stachniss](https://github.com/stachnis) and [Ignacio Vizzo](https://github.com/nachovizzo) at the University of Bonn. They own all the credits for the problems formulation and material.

Thanks to them and to the University for posting this material and all the other courses online for free.

The instructions on which this project was based can be found on this [video](https://www.youtube.com/watch?v=e2OBwMqGhzc&list=PLgnQpQtFTOGRM59sr3nSL8BmeMZR9GCIA&index=18&ab_channel=CyrillStachniss). Its development relies heavily on the course [homeworks](https://www.ipb.uni-bonn.de/teaching/cpp-2020/homeworks/), which solutions can be found on this other [repo](https://github.com/pepisg/cpp-course).

## Dependencies

To work and build the files provided in this repo you need to install the following dependencies:

### Ubuntu 20.04

To easily install alongisde Windows you can follow this [tutorial](https://itsfoss.com/install-ubuntu-1404-dual-boot-mode-windows-8-81-uefi/). The `clang` compiler should be preinstalled in this distro, however is probably a good idea to run this [script](https://raw.githubusercontent.com/wiki/nachovizzo/must-have-tools/scripts/install_llvm_toolchain.sh) to make sure you have the toolchain suggested by [Ignacio Vizzo](https://github.com/nachovizzo) for the homeworks.

### Visual Studio Code (Recommended)

I used VScode to work on this repo. To install it and use the suggested extensions and configuration you can follow these [instructions](https://github.com/nachovizzo/must-have-tools/wiki#modern-text-editors) by [Ignacio Vizzo](https://github.com/nachovizzo).

### OpenCV

Its a compile dependency for several homeworks. Its neccessary to have the full version of OpenCV to use the `sift` feature extractor. To install `OpenCV` the same way as I did you can follow these [instructions](https://github.com/nachovizzo/example_opencv#prerequisites) by [Ignacio Vizzo](https://github.com/nachovizzo).

### fmt

Its a compile dependency for the `html` visualization. You can install it using the package manager:

```.sh
sudo apt-get install libfmt-dev
```

## How to run the code?

To run the code first you need to create a folder named `dataset` in which you need to place:

1. A folder named `raw_imgs` containing all the `png` files. You can download the UniBonn dataset [here](https://uni-bonn.sciebo.de/s/c2d0a1ebbe575fdba2a35a8033f1e2ab).  
2. A folder named `sifts_bin` containing all the precomputed sift descriptors for all the images in the `raw_imgs` folder. You can do this with the code on the course's [homework_5](https://github.com/pepisg/cpp-course/tree/develop/homework_5).
3. A file named `dictionary.bin` containing the precomputed bow dictionary found applying the k-means algorithm over all the sifts descriptor. You can do this with the code on the course's [homework_9](https://github.com/pepisg/cpp-course/tree/develop/homework_9)

If you meet these requirements you can then create a `bin` folder inside the repo. Go into that folder and build the code. To do all this you can type in a terminal:

```sh
mkdir -p bin && cd bin && cmake .. && make
```

Then, while in the `bin` folder type:

```sh
./place_recognition 
```

The program will generate an html file for each image in the raw images dataset containing the 8 more simalar images among all the others.

**Disclaimer**: The code can work only using the raw images dataset, however it would need some minor changes and would take a lot computing all the sift descriptors and the dictionary. If you want to do this or you would like to use my `dictionary.bin` file and my `sifts_bin` folder leave an issue on the repo.

## Sample output

The image below shows a row of the an `html` file produced by the program.

![Screenshot from 2021-08-30 21-11-24](https://user-images.githubusercontent.com/71234974/131430509-b7521ebe-c143-477f-8348-2a9e9a0dbe6a.png)
