var photos = new Array("/home/luxe/Cpluspace/Retrieval/Img/Rotation/7_2.jpg", "/home/luxe/Cpluspace/Retrieval/Img/Rotation/7_3.jpg", "/home/luxe/Cpluspace/Retrieval/Img/Rotation/7_4.jpg", "/home/luxe/Cpluspace/Retrieval/Img/Rotation/7_1.jpg", "/home/luxe/Cpluspace/Retrieval/Img/Size/7_5.jpg", "/home/luxe/Cpluspace/Retrieval/Img/Rotation/24_2.jpg", "/home/luxe/Cpluspace/Retrieval/Img/Size/104_4.jpg", "/home/luxe/Cpluspace/Retrieval/Img/Brightness/75_3.jpg", "/home/luxe/Cpluspace/Retrieval/Img/Brightness/96_3.jpg", "/home/luxe/Cpluspace/Retrieval/Img/Rotation/24_3.jpg", "/home/luxe/Cpluspace/Retrieval/Img/Viewpoint/74_2.jpg", "/home/luxe/Cpluspace/Retrieval/Img/Size/62_4.jpg", "/home/luxe/Cpluspace/Retrieval/Img/Rotation/25_2.jpg", "/home/luxe/Cpluspace/Retrieval/Img/Rotation/40_3.jpg", "/home/luxe/Cpluspace/Retrieval/Img/Rotation/40_2.jpg", "/home/luxe/Cpluspace/Retrieval/Img/Brightness/62_3.jpg", "/home/luxe/Cpluspace/Retrieval/Img/Viewpoint/74_3.jpg", "/home/luxe/Cpluspace/Retrieval/Img/Rotation/35_3.jpg", "/home/luxe/Cpluspace/Retrieval/Img/Rotation/25_3.jpg", "/home/luxe/Cpluspace/Retrieval/Img/Rotation/35_2.jpg", "/home/luxe/Cpluspace/Retrieval/Img/Viewpoint/74_1.jpg", "/home/luxe/Cpluspace/Retrieval/Img/Rotation/35_4.jpg", "/home/luxe/Cpluspace/Retrieval/Img/Size/75_5.jpg", "/home/luxe/Cpluspace/Retrieval/Img/Viewpoint/74_4.jpg", "/home/luxe/Cpluspace/Retrieval/Img/DB/49.jpg", "/home/luxe/Cpluspace/Retrieval/Img/Size/104_5.jpg", "/home/luxe/Cpluspace/Retrieval/Img/Brightness/50_3.jpg", "/home/luxe/Cpluspace/Retrieval/Img/Brightness/63_3.jpg", "/home/luxe/Cpluspace/Retrieval/Img/Size/104_3.jpg", "/home/luxe/Cpluspace/Retrieval/Img/Brightness/49_4.jpg", "/home/luxe/Cpluspace/Retrieval/Img/Occlusion/74_1.jpg", "/home/luxe/Cpluspace/Retrieval/Img/Rotation/35_1.jpg", "/home/luxe/Cpluspace/Retrieval/Img/Brightness/91_3.jpg", "/home/luxe/Cpluspace/Retrieval/Img/Rotation/23_3.jpg", "/home/luxe/Cpluspace/Retrieval/Img/Rotation/31_2.jpg", "/home/luxe/Cpluspace/Retrieval/Img/Rotation/28_2.jpg", "/home/luxe/Cpluspace/Retrieval/Img/Brightness/59_3.jpg", "/home/luxe/Cpluspace/Retrieval/Img/Brightness/74_3.jpg", "/home/luxe/Cpluspace/Retrieval/Img/Rotation/40_1.jpg", "/home/luxe/Cpluspace/Retrieval/Img/Size/96_5.jpg", "/home/luxe/Cpluspace/Retrieval/Img/Occlusion/74_2.jpg", "/home/luxe/Cpluspace/Retrieval/Img/Brightness/78_3.jpg", "/home/luxe/Cpluspace/Retrieval/Img/Size/77_5.jpg", "/home/luxe/Cpluspace/Retrieval/Img/Brightness/101_3.jpg", "/home/luxe/Cpluspace/Retrieval/Img/Brightness/104_3.jpg", "/home/luxe/Cpluspace/Retrieval/Img/Rotation/25_4.jpg", "/home/luxe/Cpluspace/Retrieval/Img/Brightness/35_3.jpg", "/home/luxe/Cpluspace/Retrieval/Img/Rotation/23_2.jpg", "/home/luxe/Cpluspace/Retrieval/Img/Rotation/31_3.jpg", "/home/luxe/Cpluspace/Retrieval/Img/Brightness/7_4.jpg")
 for (var i = 0, photo; photo = photos[i]; i++) {
 var img = document.createElement("image");
img.src = photo;
document.body.appendChild(img); }