import { StatusBar } from "expo-status-bar";
import { Image, StyleSheet, Text, View } from "react-native";
import * as SplashScreen from "expo-splash-screen";
import { useFonts } from "expo-font";
import { useEffect } from "react";
import { router } from "expo-router";

SplashScreen.preventAutoHideAsync();
// const logo = require("./assets/images/logo.png");
const logo = require("../assets/images/logo.png");

export default function App() {
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

  useEffect(()=>{
    setTimeout(changeHomepage,1500);
  });

  if (!loaded && error) {
    return null;
  }

  return (
    <View style={styles.container}>
      <StatusBar animated backgroundColor="black" />
      <Image source={logo} style={styles.logo} />
      <Text style={styles.logoText}>My Arm</Text>
    </View>
  );
}

const styles = StyleSheet.create({
  container: {
    flex: 1,
    backgroundColor: "black",
    alignItems: "center",
    justifyContent: "center",
  },
  logo: {
    width: 100,
    height: 100,
  },
  logoText: {
    fontFamily: "roboTextLogo",
    color: "yellow",
    fontSize: 50,
    marginTop: 50,
  },
});


// js
function changeHomepage(){
    router.push("/homepage");
}