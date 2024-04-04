<div class="entry-content about-outer" itemprop="text">
    <br>
    <h2>Wetterstation des FMC Valley in Schmidham</h2>
    <p></p>
    <p>Auf dieser Seite findest Du Informationen zum technischen Aufbau sowie zur Software dieser Wetterstation</p>
    <br>
    <h3>Installation vor Ort</h3>
    <p>Die Installation befindet sich auf einem Modellflugplkatz in Oberbayern. Vor Ort gibt es natürlich weder Strom, noch einen înternetanschluß. Aus diesem Grund musste eine autark laufende Lösung gefunden werden.</p>
    <p>Diese Lösung besteht im wesentlichen aus einer Solarzelle, einem Solarladeregler und einem 12V Akku. Der Solarladeregler ist so konzipiert, dass er den Akku lädt, und an seinem Ausgang zusätzlich 12V Spannnung zur Verfügung stellt. Reicht die Leistung des Akkus nicht mehr aus, wird der 12V Ausgang abgeschaltet.</p>
    <p>Da es in den Wintermonaten und auch in den Übergangsmonaten bei schlechten Wetterverhältnissen nicht genug Strom zur gibt um die Station durchgehend zu betreiben, haben wir uns für einen Tagbetrieb entschieden.</p>
    <p>Dies bedeutet, die Anlage wir über eine Zeitschaltuhr morgens um 7 Uhr (Sommerzeit) und abends um 19 Uhr (Sommerzeit) ausgeschaltet. In der Nachtzeit ist es für uns Modellflieger werder wichtig welches Wetter herrscht, noch ist das Kamerbild von relevanz</p>
    <p>Tagsüber hingegen sind die Wetterverhältnisse, vor allem die Windverältnisse wichtig. Da wir teilweise auch eine weite Anfahrt haben hilft die  Kamera die Sicht (zB Nebel) bsser einzuschätzen.</p>
    <br>
    <h3>Eingesetzte Hardware am Flugplatz</h3>
    <p>Die Station am Flugplatz besteht aus folgenden Komponenten:</p>
    <ul>
        <li>Froggit WH 3000SE Sensorik für die Ermittlung von:
        <ul>
            <li>Außentemperatur</li>
            <li>Luftfeuchtigkeit</li>
            <li>Sonneneinstrahlung</li>
            <li>UV</li>
            <li>Niederschlag</li>
            <li<Windrichtung</li>
            <li>Windgeschwindigkeit</li>
        </ul>
        <li>Froggit DP1500 USB Gateway</li>
        <li>GL.iNet GL-A1300 (Slate Plus) WLAN Router</li>
        <li>USB LTE Stick</li>
        <li>Schaltschrank 300x200x160mm</li>
        <li>USB Hub mit 4 Ports</li>
        <li>12V Zeitschaltuhr</li>
        <li>5V Spannungsregler</li>
        <li>USB Adapter für Frontplattenmontage</li>
        <li>USB Webcam für Outdooreinsatz</li>
        <li>etwas Kabel und zwei 4mm Einbaubuchsen für 12V Zuführung</li>
    </ul>
    <br>
    <table>
      <tr>
        <th>Der Schaltkasten ist, wie auf nebenstehemdem Bild zu sehen aufgebaut. Alles wurde auf der Gitterplatte montiert. Die notwendigen Anschlüsse für Spannungszufuhr (12V) und die USB Webcam wurden nach außen verlegt. Der Rest befindet sich gesichert in der Box. Die 12V Zeitschaltuhr schaltet die +-Leitung der Spannungszuführung frei. Dann geht es auf den Spannungsregelr, der stabiliserte 5V für die Technik bereitstellt. Der USB Hub ist da dem USB Port des Routers angeschlossen. Am USB Hub wurde das LTE Modem, der Froggit DP1500, sowie die Zuleitung für die USB Webcam angeschlossen.</th>
        <th><img src="" alt="Bild techn. Aufbau Schaltkasten"</th>
      </tr>
    </table>
    <br>
    <p></p>
    <br>
    <h3>Eingesetzte Hardware zentral</h3>
    <p>Zentral kommt ein Raspberry Pi 4 zum Einsatz. Dieser wird im Rackschrank mit einem PoE Hat per Power ofer Ethernet mit Strom versorgt. Ein Adapter für eine m2.SSD dient als Basis für die Betriebssysteminstallation</p>
    <br>
    <h3>Software und Konfiguration der dezentralen Seite</h3>
    <p>Der Router auf dem Flupgplatz baut über den LTE Stick eine Internetverbidnung auf. Da es sich bei dem Router um ein Modell mit openWRT handelt wird dann eine Wireguard-VPN Verbindung zur FritzBox des Betriebers aufgebaut. </p>
    <p>Nach Aufbau der Verbindung ist es nun möglich von der zentralen Seite aus, die Installation am Flugplatz zu erreichen.</p>
    <p>Der Router am Flugplatz hat aber noch ein paar mehr Aufgaben. Er eröffnet beim Start auch ein lokales WLAN. In dieses WLAN verbindet sich das Froggit WP1500 USB Gateway. Es kann nun seine Daten an die hinterlegten Wetterdienste senden, oder an eine eigene Station. Außerdem kann von der zentralen Seite pber das VPN auf diese Daten zugegriffen werden.</p>
    <p>Außerdem erstellt der Router über einen CRON Job gesteuert alle 5 Minuten ein Bild der Webcam, formatiert es, und kopiert es auf den zentralen Server. Dies wird von einem Shell-Skript erledigt.</p>
    <p>Das Script kann hier <a href="https://github.com/cradermacher/fmc-valley/blob/main/camera.sh" target="_blank"> https://github.com/cradermacher/fmc-valley/blob/main/camera.sh</a> heruntergeladen werden</p>
    <br>
    <p>Das Kopieren des Bildes erfolgt per scp, und ist nur möglich, weil es eine zerzifikatsbasierte ssh Verbindung zwischen dem Router und dem lokal stehenden Raspberry Pi gibt.</p>
    <p>Das Bild liegt nun direkt im Webverzeichnis des Webservers und kann damit angezeigt werden.</p>
    <br>
    <h3>Software und Konfiguration auf der zentralen Seite</h3>
    <p>Zentral kommt die Software <a href="https://weewx.com" target="_blank"> weewx</a> als Wetterstationssoftware zum Einsatz</p>
    <p>Innerhalb von weewx habe ich folgende zusätzliche Software installiert:</p>
    <ul>
        <li>Treiber für Froggit DP1500 <a href="https://github.com/gjr80/weewx-gw1000" target="_blank"> https://github.com/gjr80/weewx-gw1000 </a></li>
        <li>Belchertown Skin <a href="https://github.com/poblabs/weewx-belchertown/tree/master/skins/Belchertown" target="_blank"> https://github.com/poblabs/weewx-belchertown/tree/master/skins/Belchertown </a></li>
    </ul>
    <p>An der Software sind umfangreiche Einstellungen vorgenommen worden. Die Konfigurationsdateien können meinem <a href="https://github.com/cradermacher/fmc-valley" target="_blank"> Github</a>  entnommen werden</p>
    <br>
    <br>
    <p>Hier einige Informationen zum aktuellen Stand</p>
    <ul>
        <li>Hardwaretreiber der Station: $station.hardware</li>
        <li>Server-Laufzeit: $station.os_uptime.long_form</li>
        <li>WeeWX-Laufzeit: $station.uptime.long_form</li>
        <li>WeeWX-Version: $station.version</li>
        <li>Belchertown Skin-Version: $belchertown_version</li>
    </ul>
    <br>
    <p>Bei Fragen zur Station oder zur eingesetzten Software könnt Ihr gerne auf mich zukommen.</p>
    <p></p>
</div>
