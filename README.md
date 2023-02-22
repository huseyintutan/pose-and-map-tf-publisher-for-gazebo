# pose-and-map-tf-publisher-for-gazebo

Basic ROS package for who need map transform or robot pose message with covariance.

# Clone

```
git clone https://github.com/huseyintutan/pose-and-map-tf-publisher-for-gazebo.git
```
# Run

```
rosrun map_publisher map_publisher_node
```

# Example Gazebo Plugin for Odometry
You can add this to your URDF file.
```xml
  <gazebo>
    <plugin name="p3d_base_controller" filename="libgazebo_ros_p3d.so">
      <alwaysOn>true</alwaysOn>
      <updateRate>200.0</updateRate>
      <bodyName>base_link</bodyName>
      <topicName>odom_plugin</topicName>
      <gaussianNoise>0.01</gaussianNoise>
      <frameName>world</frameName>
      <xyzOffsets>0 0 0</xyzOffsets>
      <rpyOffsets>0 0 0</rpyOffsets>
    </plugin>
  </gazebo> 

  ```
