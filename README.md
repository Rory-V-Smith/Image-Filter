# Image-Filter
Applies filters to BMPs, including: greyscale, blur, sepia, reflect, and edges (using the Sobel operator), per the below.
> $ ./filter -r image.bmp reflected.bmp

Completed in part of Harvard's [CS50 - Introduction to Computer Science, 2020](https://cs50.harvard.edu/x/2020/).
This was pset4: [Filter (more challenging)](https://cs50.harvard.edu/x/2020/psets/4/filter/more/).

### Specification
The function grayscale takes image and turns it into a black-and-white version of the same image.
The function sepia takes an image and turns it into a sepia version of the same image.
The reflect function takes an image and reflects it horizontally.
The edges function takes an image and highlights the edges between objects, according to the Sobel operator.
Finally, the blur function takes an image and turn it into a box-blurred version of the same image.
