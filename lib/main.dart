import 'package:flutter/material.dart';
import 'package:firebase_database/firebase_database.dart';
import 'package:firebase_core/firebase_core.dart';

Future<void> main() async {
  //WidgetsFlutterBinding.ensureInitialized();
  //FirebaseApp firebaseApp = await Firebase.initializeApp();
  runApp(const MyApp());
}

class MyApp extends StatelessWidget {
  const MyApp({Key? key}) : super(key: key);

  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      title: 'App',
      theme: ThemeData(
        primarySwatch: Colors.blue,
      ),
      home: const MyHomePage(title: 'Flutter Demo Home Page'),
    );
  }
}

class MyHomePage extends StatefulWidget {
  const MyHomePage({Key? key, required this.title}) : super(key: key);
  final String title;

  @override
  State<MyHomePage> createState() => _MyHomePageState();
}

class _MyHomePageState extends State<MyHomePage> {
  //final databaseReference = FirebaseDatabase.instance.reference();

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      backgroundColor: Color.fromRGBO(57, 6, 88, 100),
      appBar: AppBar(
        title: Text('USER PULSE RATE'),
        backgroundColor: Color.fromRGBO(193, 6, 73, 100),
        centerTitle: true,
      ),
      body: Center(
        child: Container(
          padding: EdgeInsets.all(20),
          margin: EdgeInsets.all(20),
          height: MediaQuery.of(context).size.height,
          width: MediaQuery.of(context).size.width,
          color: Color.fromRGBO(57, 51, 88, 100),
          child: Column(
            mainAxisAlignment: MainAxisAlignment.center,
            crossAxisAlignment: CrossAxisAlignment.center,
            children: [
              Container(
                padding: EdgeInsets.all(20),
                decoration:
                    BoxDecoration(color: Color.fromRGBO(244, 232, 236, 100)),
                child: Row(
                  mainAxisAlignment: MainAxisAlignment.spaceBetween,
                  children: [
                    Row(
                      children: [
                        Column(
                          mainAxisAlignment: MainAxisAlignment.start,
                          crossAxisAlignment: CrossAxisAlignment.end,
                          children: [
                            Text('Name: '),
                            Text('User ID: '),
                            Text('Age: '),
                            Text('Gender: '),
                          ],
                        ),
                        Column(
                          mainAxisAlignment: MainAxisAlignment.start,
                          crossAxisAlignment: CrossAxisAlignment.start,
                          children: [
                            Text(
                              'John Dow',
                              style: TextStyle(fontWeight: FontWeight.bold),
                            ),
                            Text(
                              'user_001',
                              style: TextStyle(fontWeight: FontWeight.bold),
                            ),
                            Text(
                              '31',
                              style: TextStyle(fontWeight: FontWeight.bold),
                            ),
                            Text(
                              'Male',
                              style: TextStyle(fontWeight: FontWeight.bold),
                            ),
                          ],
                        ),
                      ],
                    ),
                    Icon(
                      Icons.people_rounded,
                      size: 50,
                    )
                  ],
                ),
              ),
              SizedBox(
                height: 25,
              ),
              Container(
                padding: EdgeInsets.all(20),
                margin: EdgeInsets.all(40),
                decoration:
                    BoxDecoration(color: Color.fromRGBO(244, 232, 236, 100)),
                child: Center(
                  child: Column(
                    children: [
                      Text(
                        'PULSE RATE',
                        style: TextStyle(
                            fontWeight: FontWeight.bold, fontSize: 20),
                      ),
                      SizedBox(
                        height: 30,
                      ),
                      Text(
                        '_ _ _ _',
                        style: TextStyle(
                            fontWeight: FontWeight.bold, fontSize: 25),
                      )
                    ],
                  ),
                ),
              )
            ],
          ),
        ),
      ),
    );
  }
}
