import { Image } from "expo-image";
import { StatusBar, StyleSheet, View, Text, Pressable } from "react-native";
import * as SplashScreen from "expo-splash-screen";
import { useFonts } from "expo-font";
import { useEffect } from "react";

const upImageControl = require("../assets/images/controlImages/UP.png");
const LeftImageControl = require("../assets/images/controlImages/Left.png");
const RightImageControl = require("../assets/images/controlImages/Right.png");
const DownImageControl = require("../assets/images/controlImages/down.png");

export default function homepage() {
  // fonts
  const [loaded, error] = useFonts({
    roboTextLogo: require("../assets/fonts/Logo.ttf"),
    // lockerLight: require("../assets/fonts/LockerLight.ttf"),
  });

  useEffect(() => {
    if (loaded || error) {
      SplashScreen.hideAsync();
    }
  }, [loaded, error]);
  if (!loaded && error) {
    return null;
  }

  return (
    <View style={styles.bodyContainter}>
      <StatusBar animated backgroundColor="black" />
      <View style={styles.homeText}>
        <Text style={styles.Topic}>Contorl Center</Text>
        <Text style={styles.SecondTopic}>Contorl Your Arm</Text>
      </View>
      <View style={styles.container}>
        <View style={styles.controlPanel}>
          <View style={styles.UpControl}>
            <Pressable
              onPress={() => {
                alert("UP");
              }}
            >
              <Image source={upImageControl} style={styles.controlImages} />
            </Pressable>
          </View>
          <View style={styles.leftandRight}>
            <View style={styles.LeftControl}>
              <Pressable
                onPress={() => {
                  alert("Left");
                }}
              >
                <Image source={LeftImageControl} style={styles.controlImages} />
              </Pressable>
            </View>
            <View style={styles.RightControl}>
              <Pressable
                onPress={() => {
                  alert("right");
                }}
              >
                <Image
                  source={RightImageControl}
                  style={styles.controlImages}
                />
              </Pressable>
            </View>
          </View>
          <View style={styles.UpControl}>
            <Pressable
              onPress={() => {
                alert("bottom");
              }}
            >
              <Image source={DownImageControl} style={styles.controlImages} />
            </Pressable>
          </View>
        </View>
      </View>
    </View>
  );
}

const styles = StyleSheet.create({
  bodyContainter: {
    flex: 1,
  },
  container: {
    flex: 1,
    backgroundColor: "black",
    justifyContent: "center",
    alignItems: "center",
  },
  controlImages: {
    width: 100,
    height: 100,
  },
  controlPanel: {
    width: 350,
    height: 300,
    flexDirection: "column",
  },
  UpControl: {
    width: "100%",
    height: 100,
    alignItems: "center",
  },
  leftandRight: {
    flexDirection: "row",
  },
  LeftControl: {
    flex: 1,
    alignItems: "center",
  },
  RightControl: {
    flex: 1,
    alignItems: "center",
  },
  homeText: {
    backgroundColor: "black",
    height: 100,
    justifyContent: "center",
    alignItems: "center",
  },
  Topic: {
    color: "yellow",
    fontSize: 25,
    fontFamily: "roboTextLogo",
  },
  SecondTopic: {
    color: "yellow",
  },
});
