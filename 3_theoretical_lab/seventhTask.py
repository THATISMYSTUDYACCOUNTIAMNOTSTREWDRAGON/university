import string 

whitespace = ' \t\n\r\v\f'
ascii_letters = string.ascii_lowercase + string.ascii_uppercase
digits = '0123456789'
punctuation = r"""!"#$%&'()*+,-./:;<=>?@[\]^_`{|}~"""

salt = """\b|0"""

printable = digits + ascii_letters + punctuation + whitespace
print(printable)

song = variable = """Keine Mauer zu hoch
Keine Wege zu weit
Immer alles gewagt
Nie lang gefragt
Dem Ruf der Freiheit gefolgt
Und an das Morgen geglaubt
Nimmermüde, neues Glück
Nur nach vorn und nie zurück
Wir waren zu jung zur falschen Zeit
Und doch zum Sprung bereit
Wir wollten fliegen
Doch der Himmel war weg
Unsere Hoffnung ging zu Boden
Jetzt liegt sie neben uns im Dreck
Wir wollten frei sein
Und nicht um Liebe flehen
Doch das Leben ist 'ne Hure
Zockt dich ab und lässt dich stehen
Keine Sehnsucht zu groß
Keine Träne zu tief
Wieder alles verloren
Noch mal von vorn
Wir zerfallen zu Staub
Und wir stehen wieder auf
Neue Wege, neues Glück
Immer vorwärts, Stück für Stück
Wir waren zu jung zur falschen Zeit
Und doch zum Sprung bereit
Wir wollten fliegen
Doch der Himmel war weg
Unsere Hoffnung ging zu Boden
Jetzt liegt sie neben uns im Dreck
Wir wollten frei sein
Und nicht um Liebe flehen
Doch das Leben ist 'ne Hure
Zockt dich ab und lässt dich stehen
Unsere Zeit heilt keine Wunden
Der Schmerz kommt von allein
Wer fängt dich auf, wenn du fällst?
Wer steht für dich ein?
Wir sind nicht unzerstörbar
Doch wir halten alles aus
Wir fallen aus allen Wolken
Und dann stehen wir wieder auf
Oh, yeah
Wir wollten fliegen
Doch der Himmel war weg
Unsere Hoffnung ging zu Boden
Jetzt liegt sie neben uns im Dreck (Jetzt liegt sie neben uns im Dreck)
Wir wollten frei sein
Und nicht um Liebe flehen (Nicht um Liebe flehen)
Doch das Leben ist 'ne Hure
Zockt dich ab und lässt dich stehen
Und lässt dich stehen"""

def calculate_frequency(message: str) -> dict:
    frequency = {}
    for i in list(set(message.split())):
        frequency[i] = message.count(i)
    return dict(reversed(sorted(frequency.items(), key=lambda item: item[1])))

code_map = {}
freq = calculate_frequency(song)

for i in range(len(printable)):
    if len(freq) - 1 < i:
        break
    code_map[salt + printable[i]] =  list(freq.items())[i][0]

def encode(song, code_map):
    for i in code_map:
        song = song.replace(code_map[i], i)
    return song

def decode(song, code_map):
    for i in code_map:
        song = song.replace(i, code_map[i])
    return song

print(encode(song, code_map))
print()
print(decode(song, code_map))
