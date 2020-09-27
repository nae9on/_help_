Base64 is a binary to text encoding scheme designed to carry data stored in binary formats across channels (ex WWW) that only reliably support text content. 
It is widely used in embedding image files or other binary assets inside textual assets such as HTML and CSS files.

In this example program the following is illustrated
1. Read an image into a cv::Mat object
2. Base64 encode the cv::Mat object
3. Write the resulting string to a text file
4. Read the same string from the text file
5. Base64 decode the string
6. Convert the string back to a cv::Mat object and visualize

Additionally, it is also shown how to first compress the image into jpeg format and then Base64 encode and later
decode it (for example in note-pad++)  for visualization.

Reference and code used
https://renenyffenegger.ch/notes/development/Base64/Encoding-and-decoding-base-64-with-cpp/
https://en.wikipedia.org/wiki/Base64
