t int deg0msec = 600; // msec.
const int deg180msec = 2350; // msec.
int microSec = deg0msec;

void setup() {
    pinMode( 2, OUTPUT );
    Serial.begin( 9600 );
}

void loop() { 
    if ( Serial.available() > 0 ) {
        delay(10);
        int deg = serialReadAsInt(); 
        if ( deg >= 0 && deg <= 180 )
        microSec = deg0msec + deg / 180.0 * ( deg180msec - deg0msec );
    }

    // create PWM
    if ( microSec >= deg0msec ) {
        digitalWrite( 2, HIGH );
        delayMicroseconds( microSec ); // ON
        digitalWrite( 2, LOW );
        delayMicroseconds( 10000 ); // OFF
        delayMicroseconds( 10000 - microSec ); // OFF
    }
}

int serialReadAsInt() {
    char c[ 9 ] = "0";
    for ( int i = 0; i < 8; i++ ) {
        c[ i ] = Serial.read();
        if ( c[ i ] == '\0' )
            break;
    } 
    return atoi( c );
}

