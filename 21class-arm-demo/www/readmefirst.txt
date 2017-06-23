to play your video file:
   /motion/photo (where to modify ?)
   /var/www/motion/photo/output.mp4

to play your video file:
   /motion/photo (where to modify ?)
   /var/www/motion/photo/output.mp4

video.html:
	<video width="640" height="480" controls>
	    <source src="./motion/photo/output.mp4" type="video/mp4">
	</video>

/rootfs/usr/sbin/myconverter.sh:
	ffmpeg -i /motion/photo/videoR.avi -acodec libfaac -b:a 128k -vcodec mpeg4 -b:v 1200k -flags +aic+mv4 /var/www/motion/photo/output.mp4


to monitor camera video:

please take care of ip address.


monitor.html:
    <tr>
            <td height="500"><img src="http://172.26.1.10:8080/?action=stream" width="497" height="443"/></td>
    </tr>

