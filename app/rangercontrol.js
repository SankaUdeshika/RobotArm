import { Image } from "expo-image";
import {
  StatusBar,
  StyleSheet,
  View,
  Text,
  Pressable,
  Alert,
} from "react-native";
import * as SplashScreen from "expo-splash-screen";
import { useFonts } from "expo-font";
import { useEffect, useState } from "react";
import Slider from "@react-native-community/slider";

const upImageControl = require("../assets/images/controlImages/UP.png");
const LeftImageControl = require("../assets/images/controlImages/Left.png");
const RightImageControl = require("../assets/images/controlImages/Right.png");
const DownImageControl = require("../assets/images/controlImages/down.png");
const logo = require("../assets/images/logo.png");
const BuzzerIcon = require("../assets/images/iconImages/buzzer.png");
const MusicSecion = require("../assets/images/iconImages/music.png");

var value = 10;

export default function homepage() {
  const [getXrange, setXrange] = useState(90);
  const [getYrange, setYrange] = useState(180);
  const [getZrange, setZrange] = useState(60);

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
        <Text style={styles.SecondTopic}>Range Contorl Your Arm</Text>
        <Text style={styles.SecondTopic}>X - {getXrange}</Text>
        <Text style={styles.SecondTopic}>Y - {getYrange}</Text>
        <Text style={styles.SecondTopic}>z - {getZrange}</Text>
      </View>
      <View style={styles.container}>
        <View>
          <Pressable
            onPressIn={() => {
              RingBuzzer();
            }}
          >
            <Image source={BuzzerIcon} style={styles.BuzzerIcon} />
          </Pressable>
        </View>
        <View style={styles.controlPanel}>
          <Slider
            style={{ width: "60%", height: 40 }}
            minimumValue={0}
            maximumValue={180}
            minimumTrackTintColor="yellow"
            thumbTintColor="yellow"
            maximumTrackTintColor="yellow"
            value={90}
            onValueChange={(item) => {
              setZrange(item);
              callESP("Z", item);
            }}
          />
          {/* left Right */}
          <Slider
            style={{ width: "100%", height: 40 }}
            minimumValue={0}
            maximumValue={180}
            minimumTrackTintColor="yellow"
            thumbTintColor="yellow"
            maximumTrackTintColor="yellow"
            value={getXrange}
            onValueChange={(item) => {
              setXrange(item);
              callESP("X", item);
            }}
          />
          <Slider
            style={{
              width: "90%",
              height: 40,
              transform: [{ rotate: "270deg" }],
            }}
            minimumValue={0}
            maximumValue={180}
            minimumTrackTintColor="yellow"
            thumbTintColor="yellow"
            maximumTrackTintColor="yellow"
            value={getYrange}
            onValueChange={(item) => {
              setYrange(item);
              callESP("Y", item);
            }}
          />
        </View>
        <View style={styles.navigationCover}>
          <View style={styles.navigationBar}>
            <Pressable
              onPress={() => {
                router.push("/rangercontrol");
              }}
            >
              <Image source={MusicSecion} style={styles.MusicSecion} />
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
    backgroundColor: "black",
    justifyContent: "center",
    alignItems: "center",
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
  BuzzerIcon: {
    width: 50,
    height: 50,
  },
  // navigation
  navigationCover: {
    display: "flex",
    alignItems: "center",
    justifyContent: "center",
    position: "absolute",
    bottom: 0,
    backgroundColor: "yellow",
    width: "95%",
    height: 70,
    borderRadius: 20,
  },
  navigationBar: {
    alignItems: "center",
    justifyContent: "center",
    backgroundColor: "#EEED09",
    width: "94%",
    height: 55,
    borderRadius: 10,
  },
  MusicSecion: {
    width: 50,
    height: 50,
  },
});

async function callESP(degrees, puls) {
  var degrees;
  var puls;

  //   Alert.alert(degrees + " " + puls);

  const response = await fetch(
    "http://192.168.8.129:8080/myarmServer/RangeServletRecever?action=" +
      degrees +
      "&&puls=" +
      puls
  );
}

var value = 1;
async function RingBuzzer() {
  await fetch(
    "http://192.168.8.129:8080/myarmServer/RangeServletRecever?action=BuzzerNormal"
  );
}
