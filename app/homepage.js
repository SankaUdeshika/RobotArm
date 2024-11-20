import { StatusBar, StyleSheet, View } from "react-native";


export default function homepage(){
    return(
        <View style={styles.container}>
                 <StatusBar animated backgroundColor="black"  />

        </View>
    );
}


const styles = StyleSheet.create(
   {
    container: {
        flex:1,
        backgroundColor:"black",

    }
   }
);