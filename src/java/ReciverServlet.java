/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/JSP_Servlet/Servlet.java to edit this template
 */

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.HttpURLConnection;
import java.net.URL;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import model.motorStatus;

/**
 *
 * @author sanka
 */
@WebServlet(urlPatterns = {"/ReciverServlet"})
public class ReciverServlet extends HttpServlet {

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String action = request.getParameter("action");
        System.out.println(action);

        String targetUrl = "http://192.168.8.158?status=" + action;

        HttpURLConnection connection = null;
        BufferedReader reader = null;

        try {
            // Create and configure the connection
            URL url = new URL(targetUrl);
            connection = (HttpURLConnection) url.openConnection();
            connection.setRequestMethod("GET"); // Use POST if needed
            connection.setConnectTimeout(5000); // 5-second connection timeout
            connection.setReadTimeout(5000);    // 5-second read timeout
            connection.setRequestProperty("Accept", "application/json");

            // Send the request and get the response code
            int responseCode = connection.getResponseCode(); // This sends the request
            System.out.println("Response Code: " + responseCode);

            // If successful, read the response
            if (responseCode == HttpURLConnection.HTTP_OK) {
                reader = new BufferedReader(new InputStreamReader(connection.getInputStream()));
                String inputLine;
                StringBuffer responseContent = new StringBuffer();
                while ((inputLine = reader.readLine()) != null) {
                    responseContent.append(inputLine);
                }
                // Log response content if needed
                System.out.println("Response: " + responseContent.toString());
            }

        } catch (IOException e) {
            e.printStackTrace();
            throw new ServletException("Failed to send request: " + e.getMessage(), e);

        } finally {
            // Ensure the connection is closed
            if (connection != null) {
                connection.disconnect();
            }
            if (reader != null) {
                reader.close();
            }
        }

        // Send a basic response back to the client
        response.setContentType("text/plain");
        response.getWriter().write("Request sent to " + targetUrl);
    }

}
