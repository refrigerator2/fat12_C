/*
 * Unit Test Bootstrap
 * Autor: Tomasz Jaworski, 2018-2020
 *
 * Test dla zadania Projekt: czytnik dysku, woluminu, katalogu głównego i plików (3,0)
 * Autor testowanej odpowiedzi: Tsimur Makarevich
 * Test wygenerowano automatycznie o 2026-10-26 11:06:35.376222
 *
 * Debug: 
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <signal.h>
#include <setjmp.h>
#include <assert.h>

#if !defined(__clang__) && !defined(__GNUC__)
// Zakomentuj poniższy błąd, jeżeli chcesz przetestować testy na swoim kompilatorze C.
#error System testow jednostkowych jest przeznaczony dla kompilatorów GCC/Clang.
#endif

#if defined(_WIN32) || defined(_WIN64) || defined(__CYGWIN__)
// Zakomentuj poniższy błąd, jeżeli chcesz przetestować testy na platformie Windows.
#error System testow jednostkowych NIE jest przeznaczony dla testów uruchamianych na platformach Windows.
#endif

#define _RLDEBUG_API_
#include "unit_helper_v2.h"
#include "rdebug.h"

#include "tested_declarations.h"
#include "rdebug.h"

//
// Elementy globalne dla całego testu
//




//
//  Test 1: Sprawdzanie poprawności działania funkcji disk_open_from_file
//
void UTEST1(void)
{
    // informacje o teście
    test_start(1, "Sprawdzanie poprawności działania funkcji disk_open_from_file", __LINE__);

    // uwarunkowanie zasobów - pamięci, itd...
    test_file_write_limit_setup(33554432);
    rldebug_reset_limits();
    
    //
    // -----------
    //
    


            struct disk_t* disk = disk_open_from_file("GOLD");
            test_error(disk == NULL, "Funkcja disk_open_from_file() powinna zwrócić NULL przy próbie otwarcia nieistniejącego pliku");

            test_no_heap_leakage();
            onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)
        
    //
    // -----------
    //

    // przywrócenie podstawowych parametów przydzielania zasobów (jeśli to tylko możliwe)
    rldebug_reset_limits();
    test_file_write_limit_restore();
    
    test_ok();
}

//
//  Test 2: Sprawdzanie poprawności działania funkcji disk_open_from_file
//
void UTEST2(void)
{
    // informacje o teście
    test_start(2, "Sprawdzanie poprawności działania funkcji disk_open_from_file", __LINE__);

    // uwarunkowanie zasobów - pamięci, itd...
    test_file_write_limit_setup(33554432);
    rldebug_reset_limits();
    
    //
    // -----------
    //
    


            struct disk_t* disk = disk_open_from_file(NULL);
            test_error(disk == NULL, "Funkcja disk_open_from_file() powinna zwrócić NULL przy próbie otwarcia nieistniejącego pliku");

            test_no_heap_leakage();
            onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)
        
    //
    // -----------
    //

    // przywrócenie podstawowych parametów przydzielania zasobów (jeśli to tylko możliwe)
    rldebug_reset_limits();
    test_file_write_limit_restore();
    
    test_ok();
}

//
//  Test 3: Sprawdzanie poprawności działania funkcji disk_close
//
void UTEST3(void)
{
    // informacje o teście
    test_start(3, "Sprawdzanie poprawności działania funkcji disk_close", __LINE__);

    // uwarunkowanie zasobów - pamięci, itd...
    test_file_write_limit_setup(33554432);
    rldebug_reset_limits();
    
    //
    // -----------
    //
    


            disk_close(NULL);
      
            test_no_heap_leakage();
            onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)
        
    //
    // -----------
    //

    // przywrócenie podstawowych parametów przydzielania zasobów (jeśli to tylko możliwe)
    rldebug_reset_limits();
    test_file_write_limit_restore();
    
    test_ok();
}

//
//  Test 4: Sprawdzanie poprawności działania funkcji fat_open
//
void UTEST4(void)
{
    // informacje o teście
    test_start(4, "Sprawdzanie poprawności działania funkcji fat_open", __LINE__);

    // uwarunkowanie zasobów - pamięci, itd...
    test_file_write_limit_setup(33554432);
    rldebug_reset_limits();
    
    //
    // -----------
    //
    


            struct disk_t* disk = disk_open_from_file("ice.img");
            test_error(disk != NULL, "Funkcja disk_open_from_file() niepoprawnie otworzyła plik");

            struct volume_t* volume = fat_open(disk, 0);
            test_error(volume == NULL, "Funkcja fat_open() powinna zwrócić NULL w przypadku przekazania błędnego obrazu dysku");
            onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)

            disk_close(disk);

            test_no_heap_leakage();
            onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)
        
    //
    // -----------
    //

    // przywrócenie podstawowych parametów przydzielania zasobów (jeśli to tylko możliwe)
    rldebug_reset_limits();
    test_file_write_limit_restore();
    
    test_ok();
}

//
//  Test 5: Sprawdzanie poprawności działania funkcji disk_open_from_file
//
void UTEST5(void)
{
    // informacje o teście
    test_start(5, "Sprawdzanie poprawności działania funkcji disk_open_from_file", __LINE__);

    // uwarunkowanie zasobów - pamięci, itd...
    test_file_write_limit_setup(33554432);
    rldebug_reset_limits();
    
    //
    // -----------
    //
    

            struct volume_t* volume = fat_open(NULL, 0);
            test_error(volume == NULL, "Funkcja fat_open() powinna zwrócić NULL w przypadku przekazania błędnego obrazu dysku");

            test_no_heap_leakage();
            onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)
        
    //
    // -----------
    //

    // przywrócenie podstawowych parametów przydzielania zasobów (jeśli to tylko możliwe)
    rldebug_reset_limits();
    test_file_write_limit_restore();
    
    test_ok();
}

//
//  Test 6: Sprawdzanie poprawności działania funkcji file_read
//
void UTEST6(void)
{
    // informacje o teście
    test_start(6, "Sprawdzanie poprawności działania funkcji file_read", __LINE__);

    // uwarunkowanie zasobów - pamięci, itd...
    test_file_write_limit_setup(33554432);
    rldebug_reset_limits();
    
    //
    // -----------
    //
    
        
                char *filecontent = (char *)calloc(3421, 1);
                char expected_filecontent[3422] = "";
        
                strcat(expected_filecontent, "His wings are pointed, for there always throng\nAll such as not to Archeron descend.\"\n     Then I: \"If new laws have not quite destroy\'d\nMemory and use of that sweet song of love,\nThat while all my cares had power to \'swage;\nPlease thee with it a little to console\nMy spirit, that incumber\'d with its frame,\nTravelling so far, of pain is overcome.\"\n     \"Love that discourses in my thoughts.\"  He then\nBegan in such soft accents, that within\nThe sweetness thrills me yet.  My gentle guide\nAnd all who came with him, so well were pleas\'d,\nThat seem\'d naught else might in their thoughts have room.\n     Fast fix\'d in mute attention to his notes\nWe stood, when lo!  that old man venerable\nExclaiming, \"How is this, ye tardy spirits?\nWhat negligence detains you loit\'ring here?\nRun to the mountain to cast off those scales,\nThat from your eyes the sight of God conceal.\"\n     As a wild flock of pigeons, to their food\nCollected, blade or tares, without their pride\nAccustom\'d, and in still and quiet sort,\nIf aught alarm them, suddenly desert\nTheir meal, assail\'d by more important care;\nSo I that new-come troop beheld, the song\nDeserting, hasten to the mountain\'s side,\nAs one who goes yet where he tends knows not.\n     Nor with less hurried step did we depart.\n\n\n\nCANTO III\n\nThem sudden flight had scatter\'d over the plain,\nTurn\'d tow\'rds the mountain, whither reason\'s voice\nDrives us; I to my faithful company\nAdhering, left it not.  For how of him\nDepriv\'d, might I have sped, or who beside\nWould o\'er the mountainous tract have led my steps\nHe with the bitter pang of self-remorse\nSeem\'d smitten.  O clear conscience and upright\nHow doth a little fling wound thee sore!\n     Soon as his feet desisted (slack\'ning pace),\nFrom haste, that mars all decency of act,\nMy mind, that in itself before was wrapt,\nIts thoughts expanded, as with joy restor\'d:\nAnd full against the steep ascent I set\nMy face, where highest to heav\'n its top o\'erflows.\n     The sun, that flar\'d behind, with ruddy beam\nBefore my form was broken; for in me\nHis rays resistance met.  I turn\'d aside\nWith fear of being left, when I beheld\nOnly before myself the ground obscur\'d.\nWhen thus my solace, turning him around,\nBespake me kindly:  \"Why distrustest thou?\nBeliev\'st not I am with thee, thy sure guide?\nIt now is evening there, where buried lies\nThe body, in which I cast a shade, remov\'d\nTo Naples from Brundusium\'s wall.  Nor thou\nMarvel, if before me no shadow fall,\nMore than that in the sky element\nOne ray obstructs not other.  To endure\nTorments of heat and cold extreme, like frames\nThat virtue hath dispos\'d, which how it works\nWills not to us should be reveal\'d.  Insane\nWho hopes, our reason may that space explore,\nWhich holds three persons in one substance knit.\nSeek not the wherefore, race of human kind;\nCould ye have seen the whole, no need had been\nFor Mary to bring forth.  Moreover ye\nHave seen such men desiring fruitlessly;\nTo whose desires repose would have been giv\'n,\nThat now but serve them for eternal grief.\nI speak of Plato, and the Stagyrite,\nAnd others many more.\"  And then he bent\nDownwards his forehead, and in troubled mood\nBroke off his speech.  Meanwhile we had arriv\'d\nFar as the mountain\'s foot, and there the rock\nFound of so steep ascent, that nimblest steps\nTo climb it had been vain.  The most remote\nMost wild untrodden path, in all the tract\n\'Twixt Lerice and Turbia were to this\nA ladder easy\' an");
                
        
                struct disk_t* disk = disk_open_from_file("subtract_fat12_volume.img");
                test_error(disk != NULL, "Funkcja disk_open_from_file() niepoprawnie otworzyła plik");
                onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)
        
                struct volume_t* volume = fat_open(disk, 0);
                test_error(volume != NULL, "Funkcja fat_open() niepoprawnie otworzyła wolumin");
                onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)
        
                struct file_t* file = file_open(volume, "TAIL");
                test_error(file != NULL, "Funkcja file_open() niepoprawnie otworzyła plik");
                onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)
        
                size_t size = file_read(filecontent, 1, 3421, file);
                test_error(size == 3421, "Funkcja file_read() niepoprawnie wczytała dane z pliku, powinna wczytać 3421 bajtów, a wczytała %lu", size);
                onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)

                int diff_pos = mem_find_first_difference(filecontent, expected_filecontent, 3421);
            
                // jeśli jest, to raportuj błąd
                test_error(diff_pos == -1, "Dane wczytane z pliku nie są poprawne; różnica w bajcie %d; jest 0x%02x a powinno być 0x%02x",
                    diff_pos, mem_get_byte(filecontent, diff_pos), mem_get_byte(expected_filecontent, diff_pos));
            
                onerror_compare_memory(expected_filecontent, filecontent, 3421);


                free(filecontent);
        
                file_close(file);
                fat_close(volume);
                disk_close(disk);
        
                test_no_heap_leakage();
                onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)
            
    //
    // -----------
    //

    // przywrócenie podstawowych parametów przydzielania zasobów (jeśli to tylko możliwe)
    rldebug_reset_limits();
    test_file_write_limit_restore();
    
    test_ok();
}

//
//  Test 7: Sprawdzanie poprawności działania funkcji file_read
//
void UTEST7(void)
{
    // informacje o teście
    test_start(7, "Sprawdzanie poprawności działania funkcji file_read", __LINE__);

    // uwarunkowanie zasobów - pamięci, itd...
    test_file_write_limit_setup(33554432);
    rldebug_reset_limits();
    
    //
    // -----------
    //
    
        
                char *filecontent = (char *)calloc(3749, 1);
                char expected_filecontent[3750] = "";
        
                strcat(expected_filecontent, "seaport on the\nconfines of the Maremma, has led them to conceive hopes of\nbecoming a naval power: but this scheme will prove as chimerical\nas their former plan for the discovery of a subterraneous stream\nunder their city.\"  Why they gave the appellation of Diana to the\nimagined stream, Venturi says he leaves it to the antiquaries of\nSienna to conjecture.\n\nCANTO XIV\n\nv. 34.  Maim\'d of Pelorus.]  Virg. Aen. 1. iii. 414.\n\n--a hill\nTorn from Pelorus\nMilton P. L. b. i. 232\n\nv. 45.  \'Midst brute swine.]  The people of Casentino.\n\nv. 49.  Curs.]  The Arno leaves Arezzo about four miles to the\nleft.\n\nv. 53.  Wolves.]  The Florentines.\n\nv. 55.  Foxes.]  The Pisans\n\nv. 61.  Thy grandson.]  Fulcieri de\' Calboli, grandson of\nRinieri de\' Calboli, who is here spoken to.  The atrocities\npredicted came to pass in 1302.  See G. Villani, 1.  viii c. 59\n\nv. 95.  \'Twixt Po, the mount, the Reno, and the shore.]  The\nboundaries of Romagna.\n\nv. 99.  Lizio.]  Lizio da Valbona, introduced into Boccaccio\'s\nDecameron, G. v. N, 4.\n\nv. 100.  Manardi, Traversaro, and Carpigna.1 Arrigo Manardi of\nFaenza, or as some say, of Brettinoro, Pier Traversaro, lord of\nRavenna, and Guido di Carpigna of Montefeltro.\n\nv. 102.  In Bologna the low artisan.]  One who had been a\nmechanic named Lambertaccio, arrived at almost supreme power in\nBologna.\n\nv. 103.  Yon Bernardin.]  Bernardin di Fosco, a man of low\norigin but great talents, who governed at Faenza.\n\nv. 107.  Prata.]  A place between Faenza and Ravenna\n\nv. 107.  Of Azzo him.] Ugolino of the Ubaldini family in Tuscany\nHe is recounted among the poets by Crescimbeni and Tiraboschi.\n\nv. 108.  Tignoso.] Federigo Tignoso of Rimini.\n\nv. 109.  Traversaro\'s house and Anastagio\'s.]  Two noble families\nof Ravenna.  She to whom Dryden has given the name of Honoria, in\nthe fable so admirably paraphrased from Boccaccio, was of the\nformer: her lover and the specter were of the Anastagi family.\n\nv. 111.  The ladies, &c.]  These two lines express the true\nspirit of chivalry.  \"Agi\" is understood by the commentators whom\nI have consulted,to mean \"the ease procured for others by the\nexertions of knight-errantry.\"  But surely it signifies the\nalternation of ease with labour.\n\nv. 114.  O Brettinoro.]  A beautifully situated castle in\nRomagna, the hospitable residence of Guido del Duca, who is here\nspeaking.\n\nv. 118.  Baynacavallo.]  A castle between Imola and Ravenna\n\nv. 118.  Castracaro ill\nAnd Conio worse.]  Both in Romagna.\n\nv. 121.  Pagani.]  The Pagani were lords of Faenza and Imola. One\nof them Machinardo, was named the Demon, from his treachery.\nSee Hell, Canto XXVII. 47, and Note.\n\nv. 124.  Hugolin.]  Ugolino Ubaldini, a noble and virtuous person\nin Faenza, who, on account of his age probably, was not likely to\nleave any offspring behind him.  He is enumerated among the poets\nby Crescimbeni, and Tiraboschi.  Mr. Matthias\'s edit. vol. i. 143\n\nv. 136.  Whosoever finds Will slay me.] The words of Cain, Gen.\ne. iv. 14.\n\nv. 142.  Aglauros.]  Ovid, Met.  I, ii.  fate. 12.\n\nv. 145.  There was the galling bit.]  Referring to what had been\nbefore said, Canto XIII.  35.\n\nCANTO XV\n\nv. 1.  As much.]  It wanted three hours of sunset.\n\nv. 16.  As when the ray.]  Compare Virg. Aen. 1.viii. 22, and\nApol. Rhod. 1. iii. 755.\n\nv. 19.  Ascending at a glance.]  Lucretius, 1. iv. 215.\n\nv. 20.  Differs from the stone.]  The motion of light being\nquicker  than that of a stone through an equal space.\n\nv. 38.  Blessed the merciful.  Matt. c. v. 7.\n\nv. 43.  Romagna\'s spirit.] Guido del Duea, of Brettinoro whom we\nhave seen in the preceding Canto.\n\nv. 87.  A dame.]  Luke, c. ii.  18\n\nv. 101.  How shall we those requite.]  The answer of Pisistratus\nthe tyrant to his wife, when she urged him to inflict the\npun");
                
        
                struct disk_t* disk = disk_open_from_file("subtract_fat12_volume.img");
                test_error(disk != NULL, "Funkcja disk_open_from_file() niepoprawnie otworzyła plik");
                onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)
        
                struct volume_t* volume = fat_open(disk, 0);
                test_error(volume != NULL, "Funkcja fat_open() niepoprawnie otworzyła wolumin");
                onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)
        
                struct file_t* file = file_open(volume, "MULTIPLY.BIN");
                test_error(file != NULL, "Funkcja file_open() niepoprawnie otworzyła plik");
                onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)
        
                size_t size = file_read(filecontent, 1, 3749, file);
                test_error(size == 3749, "Funkcja file_read() niepoprawnie wczytała dane z pliku, powinna wczytać 3749 bajtów, a wczytała %lu", size);
                onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)

                int diff_pos = mem_find_first_difference(filecontent, expected_filecontent, 3749);
            
                // jeśli jest, to raportuj błąd
                test_error(diff_pos == -1, "Dane wczytane z pliku nie są poprawne; różnica w bajcie %d; jest 0x%02x a powinno być 0x%02x",
                    diff_pos, mem_get_byte(filecontent, diff_pos), mem_get_byte(expected_filecontent, diff_pos));
            
                onerror_compare_memory(expected_filecontent, filecontent, 3749);


                free(filecontent);
        
                file_close(file);
                fat_close(volume);
                disk_close(disk);
        
                test_no_heap_leakage();
                onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)
            
    //
    // -----------
    //

    // przywrócenie podstawowych parametów przydzielania zasobów (jeśli to tylko możliwe)
    rldebug_reset_limits();
    test_file_write_limit_restore();
    
    test_ok();
}

//
//  Test 8: Sprawdzanie poprawności działania funkcji file_read
//
void UTEST8(void)
{
    // informacje o teście
    test_start(8, "Sprawdzanie poprawności działania funkcji file_read", __LINE__);

    // uwarunkowanie zasobów - pamięci, itd...
    test_file_write_limit_setup(33554432);
    rldebug_reset_limits();
    
    //
    // -----------
    //
    
        
                char *filecontent = (char *)calloc(3364, 1);
                char expected_filecontent[3365] = "";
        
                strcat(expected_filecontent, "wond\'ring and suspense,\nReplied:  \"I see that thou believ\'st these things,\nBecause I tell them, but discern\'st not how;\nSo that thy knowledge waits not on thy faith:\nAs one who knows the name of thing by rote,\nBut is a stranger to its properties,\nTill other\'s tongue reveal them.  Fervent love\nAnd lively hope with violence assail\nThe kingdom of the heavens, and overcome\nThe will of the Most high; not in such sort\nAs man prevails o\'er man; but conquers it,\nBecause \'t is willing to be conquer\'d, still,\nThough conquer\'d, by its mercy conquering.\n     \"Those, in the eye who live the first and fifth,\nCause thee to marvel, in that thou behold\'st\nThe region of the angels deck\'d with them.\nThey quitted not their bodies, as thou deem\'st,\nGentiles but Christians, in firm rooted faith,\nThis of the feet in future to be pierc\'d,\nThat of feet nail\'d already to the cross.\nOne from the barrier of the dark abyss,\nWhere never any with good will returns,\nCame back unto his bones.  Of lively hope\nSuch was the meed; of lively hope, that wing\'d\nThe prayers sent up to God for his release,\nAnd put power into them to bend his will.\nThe glorious Spirit, of whom I speak to thee,\nA little while returning to the flesh,\nBeliev\'d in him, who had the means to help,\nAnd, in believing, nourish\'d such a flame\nOf holy love, that at the second death\nHe was made sharer in our gamesome mirth.\nThe other, through the riches of that grace,\nWhich from so deep a fountain doth distil,\nAs never eye created saw its rising,\nPlac\'d all his love below on just and right:\nWherefore of grace God op\'d in him the eye\nTo the redemption of mankind to come;\nWherein believing, he endur\'d no more\nThe filth of paganism, and for their ways\nRebuk\'d the stubborn nations.  The three nymphs,\nWhom at the right wheel thou beheldst advancing,\nWere sponsors for him more than thousand years\nBefore baptizing.  O how far remov\'d,\nPredestination!  is thy root from such\nAs see not the First cause entire: and ye,\nO mortal men!  be wary how ye judge:\nFor we, who see our Maker, know not yet\nThe number of the chosen: and esteem\nSuch scantiness of knowledge our delight:\nFor all our good is in that primal good\nConcentrate, and God\'s will and ours are one.\"\n     So, by that form divine, was giv\'n to me\nSweet medicine to clear and strengthen sight,\nAnd, as one handling skillfully the harp,\nAttendant on some skilful songster\'s voice\nBids the chords vibrate, and therein the song\nAcquires more pleasure; so, the whilst it spake,\nIt doth remember me, that I beheld\nThe pair of blessed luminaries move.\nLike the accordant twinkling of two eyes,\nTheir beamy circlets, dancing to the sounds.\n\n\n\nCANTO XXI\n\nAgain mine eyes were fix\'d on Beatrice,\nAnd with mine eyes my soul, that in her looks\nFound all contentment.  Yet no smile she wore\nAnd, \"Did I smile,\" quoth she, \"thou wouldst be straight\nLike Semele when into ashes turn\'d:\nFor, mounting these eternal palace-stairs,\nMy beauty, which the loftier it climbs,\nAs thou hast noted, still doth kindle more,\nSo shines, that, were no temp\'ring interpos\'d,\nThy mortal puissance would from its rays\nShrink, as the leaf doth from the thunderbolt.\nInto the seventh splendour are we wafted,\nThat underneath the burning lion\'s breast\nBeams, in this hour, commingled with his might,\nThy mind be with thine eyes: and in them mirror\'d\nThe shape, which in this mirror sha");
                
        
                struct disk_t* disk = disk_open_from_file("subtract_fat12_volume.img");
                test_error(disk != NULL, "Funkcja disk_open_from_file() niepoprawnie otworzyła plik");
                onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)
        
                struct volume_t* volume = fat_open(disk, 0);
                test_error(volume != NULL, "Funkcja fat_open() niepoprawnie otworzyła wolumin");
                onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)
        
                struct file_t* file = file_open(volume, "THOUSAND.TXT");
                test_error(file != NULL, "Funkcja file_open() niepoprawnie otworzyła plik");
                onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)
        
                size_t size = file_read(filecontent, 1, 3364, file);
                test_error(size == 3364, "Funkcja file_read() niepoprawnie wczytała dane z pliku, powinna wczytać 3364 bajtów, a wczytała %lu", size);
                onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)

                int diff_pos = mem_find_first_difference(filecontent, expected_filecontent, 3364);
            
                // jeśli jest, to raportuj błąd
                test_error(diff_pos == -1, "Dane wczytane z pliku nie są poprawne; różnica w bajcie %d; jest 0x%02x a powinno być 0x%02x",
                    diff_pos, mem_get_byte(filecontent, diff_pos), mem_get_byte(expected_filecontent, diff_pos));
            
                onerror_compare_memory(expected_filecontent, filecontent, 3364);


                free(filecontent);
        
                file_close(file);
                fat_close(volume);
                disk_close(disk);
        
                test_no_heap_leakage();
                onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)
            
    //
    // -----------
    //

    // przywrócenie podstawowych parametów przydzielania zasobów (jeśli to tylko możliwe)
    rldebug_reset_limits();
    test_file_write_limit_restore();
    
    test_ok();
}

//
//  Test 9: Sprawdzanie poprawności działania funkcji file_read
//
void UTEST9(void)
{
    // informacje o teście
    test_start(9, "Sprawdzanie poprawności działania funkcji file_read", __LINE__);

    // uwarunkowanie zasobów - pamięci, itd...
    test_file_write_limit_setup(33554432);
    rldebug_reset_limits();
    
    //
    // -----------
    //
    
        
                char *filecontent = (char *)calloc(3027, 1);
                char expected_filecontent[3028] = "";
        
                strcat(expected_filecontent, "onferred by that family on our poet at a subsequent perid of his\nexile in 1307.\n\n\n\nCanto XXV\n\nv.1.  The sinner ]  So Trissino\n        Poi facea con le man le fiche al cielo\n        Dicendo:  Togli, Iddio; che puoi piu farmi?\n               L\'ital. Lib. c. xii\n\nv. 12.  Thy seed]  Thy ancestry.\n\nv. 15.  Not him]  Capanaeus.  Canto XIV.\n\nv. 18.  On Marenna\'s marsh.]  An extensive tract near the\nsea-shore in Tuscany.\n\nv. 24.  Cacus.]  Virgil, Aen. l. viii. 193.\n\nv. 31.  A hundred blows.]  Less than ten blows, out of the\nhundred Hercules gave him, deprived him of feeling.\n\nv. 39.  Cianfa]  He is said to have been of the family of Donati\nat Florence.\n\nv. 57.  Thus up the shrinking paper.]\n        --All my bowels crumble up to dust.\n        I am a scribbled form, drawn up with a pen\n        Upon a parchment; and against this fire\n        Do I shrink up.\n               Shakespeare, K. John, a. v. s. 7.\n\nv. 61.  Agnello.]  Agnello Brunelleschi\n\nv. 77.  In that part.]  The navel.\n\nv. 81.  As if by sleep or fev\'rous fit assail\'d.]\n               O Rome!  thy head\n        Is drown\'d in sleep, and all thy body fev\'ry.\n               Ben Jonson\'s Catiline.\n\nv. 85.  Lucan.]  Phars. l. ix. 766 and 793.\n\nv. 87.  Ovid.] Metam. l. iv. and v.\n\nv. 121.  His sharpen\'d visage.]  Compare Milton, P. L. b. x. 511\n&c.\n\nv. 131.  Buoso.]  He is said to have been of the Donati family.\n\nv. 138.  Sciancato.]  Puccio Sciancato, a noted robber, whose\nfamilly, Venturi says, he has not been able to discover.\n\nv. 140.  Gaville.]  Francesco Guercio Cavalcante was killed at\nGaville, near Florence; and in revenge of his death several\ninhabitants of that district were put to death.\n\nCANTO XXVI\n\nv. 7. But if our minds.]\n\n        Namque sub Auroram, jam dormitante lucerna,\n        Somnia quo cerni tempore vera solent.\n               Ovid, Epist. xix\n\nThe same poetical superstition is alluded to in the Purgatory,\nCant. IX. and XXVII.\n\nv. 9. Shall feel what Prato.]  The poet prognosticates the\ncalamities which were soon to befal his native city, and which he\nsays, even her nearest neighbor, Prato, would wish her.  The\ncalamities more particularly pointed at, are said to be the fall\nof a wooden bridge over the Arno, in May, 1304, where a large\nmultitude were assembled to witness a representation  of hell nnd\nthe infernal torments, in consequence of which accident many\nlives were lost; and a conflagration that in the following month\ndestroyed more than seventeen hundred houses, many ofthem\nsumptuous buildings.  See G. Villani, Hist. l. viii. c. 70 and\n71.\n\nv. 22.  More than I am wont.]  \"When I reflect on the punishment\nallotted to those who do not give sincere and upright advice to\nothers I am more anxious than ever not to abuse to so bad a\npurpose those talents, whatever they may be, which Nature, or\nrather Providence, has conferred on me.\"  It is probable that\nthis declaration was the result of real feeling Textd have\ngiven great weight to\nany opinion or party he had espoused, and to whom indigence and\nexile might h");
                
        
                struct disk_t* disk = disk_open_from_file("subtract_fat12_volume.img");
                test_error(disk != NULL, "Funkcja disk_open_from_file() niepoprawnie otworzyła plik");
                onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)
        
                struct volume_t* volume = fat_open(disk, 0);
                test_error(volume != NULL, "Funkcja fat_open() niepoprawnie otworzyła wolumin");
                onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)
        
                struct file_t* file = file_open(volume, "LIFE");
                test_error(file != NULL, "Funkcja file_open() niepoprawnie otworzyła plik");
                onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)
        
                size_t size = file_read(filecontent, 1, 3027, file);
                test_error(size == 3027, "Funkcja file_read() niepoprawnie wczytała dane z pliku, powinna wczytać 3027 bajtów, a wczytała %lu", size);
                onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)

                int diff_pos = mem_find_first_difference(filecontent, expected_filecontent, 3027);
            
                // jeśli jest, to raportuj błąd
                test_error(diff_pos == -1, "Dane wczytane z pliku nie są poprawne; różnica w bajcie %d; jest 0x%02x a powinno być 0x%02x",
                    diff_pos, mem_get_byte(filecontent, diff_pos), mem_get_byte(expected_filecontent, diff_pos));
            
                onerror_compare_memory(expected_filecontent, filecontent, 3027);


                free(filecontent);
        
                file_close(file);
                fat_close(volume);
                disk_close(disk);
        
                test_no_heap_leakage();
                onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)
            
    //
    // -----------
    //

    // przywrócenie podstawowych parametów przydzielania zasobów (jeśli to tylko możliwe)
    rldebug_reset_limits();
    test_file_write_limit_restore();
    
    test_ok();
}

//
//  Test 10: Sprawdzanie poprawności działania funkcji file_read
//
void UTEST10(void)
{
    // informacje o teście
    test_start(10, "Sprawdzanie poprawności działania funkcji file_read", __LINE__);

    // uwarunkowanie zasobów - pamięci, itd...
    test_file_write_limit_setup(33554432);
    rldebug_reset_limits();
    
    //
    // -----------
    //
    
        
                char *filecontent = (char *)calloc(3647, 1);
                char expected_filecontent[3648] = "";
        
                strcat(expected_filecontent, "nd tears\nFollow so closely on the passion prompts them,\nThey wait not for the motions of the will\nIn natures most sincere.  I did but smile,\nAs one who winks; and thereupon the shade\nBroke off, and peer\'d into mine eyes, where best\nOur looks interpret. \"So to good event\nMayst thou conduct such great emprize,\" he cried,\n\"Say, why across thy visage beam\'d, but now,\nThe lightning of a smile!\"  On either part\nNow am I straiten\'d; one conjures me speak,\nTh\' other to silence binds me: whence a sigh\nI utter, and the sigh is heard.  \"Speak on; \"\nThe teacher cried;  \"and do not fear to speak,\nBut tell him what so earnestly he asks.\"\nWhereon I thus:  \"Perchance, O ancient spirit!\nThou marvel\'st at my smiling. There is room\nFor yet more wonder.  He who guides my ken\nOn high, he is that Mantuan, led by whom\nThou didst presume of men arid gods to sing.\nIf other cause thou deem\'dst for which I smil\'d,\nLeave it as not the true one; and believe\nThose words, thou spak\'st of him, indeed the cause.\"\n     Now down he bent t\' embrace my teacher\'s feet;\nBut he forbade him:  \"Brother!  do it not:\nThou art a shadow, and behold\'st a shade.\"\nHe rising answer\'d thus:  \"Now hast thou prov\'d\nThe force and ardour of the love I bear thee,\nWhen I forget we are but things of air,\nAnd as a substance treat an empty shade.\"\n\n\n\nCANTO XXII\n\nNow we had left the angel, who had turn\'d\nTo the sixth circle our ascending step,\nOne gash from off my forehead raz\'d: while they,\nWhose wishes tend to justice, shouted forth:\n\"Blessed!\"  and ended with, \"I thirst:\" and I,\nMore nimble than along the other straits,\nSo journey\'d, that, without the sense of toil,\nI follow\'d upward the swift-footed shades;\nWhen Virgil thus began:  \"Let its pure flame\nFrom virtue flow, and love can never fail\nTo warm another\'s bosom\' so the light\nShine manifestly forth.  Hence from that hour,\nWhen \'mongst us in the purlieus of the deep,\nCame down the spirit of Aquinum\'s hard,\nWho told of thine affection, my good will\nHath been for thee of quality as strong\nAs ever link\'d itself to one not seen.\nTherefore these stairs will now seem short to me.\nBut tell me: and if too secure I loose\nThe rein with a friend\'s license, as a friend\nForgive me, and speak now as with a friend:\nHow chanc\'d it covetous desire could find\nPlace in that bosom, \'midst such ample store\nOf wisdom, as thy zeal had treasur\'d there?\"\n     First somewhat mov\'d to laughter by his words,\nStatius replied: \"Each syllable of thine\nIs a dear pledge of love.  Things oft appear\nThat minister false matters to our doubts,\nWhen their true causes are remov\'d from sight.\nThy question doth assure me, thou believ\'st\nI was on earth a covetous man, perhaps\nBecause thou found\'st me in that circle plac\'d.\nKnow then I was too wide of avarice:\nAnd e\'en for that excess, thousands of moons\nHave wax\'d and wan\'d upon my sufferings.\nAnd were it not that I with heedful care\nNoted where thou exclaim\'st as if in ire\nWith human nature, \'Why, thou cursed thirst\nOf gold!  dost not with juster measure guide\nThe appetite of mortals?\'  I had met\nThe fierce encounter of the voluble rock.\nThen was I ware that with too ample wing\nThe hands may haste to lavishment, and turn\'d,\nAs from my other evil, so from this\nIn penitence.  How many from their grave\nShall with shorn locks arise, who living, aye\nAnd at life\'s last extreme, of this offence,\nThrough ignorance, did not repent.  And know,\nThe fault which lies direct from any sin\nIn level opposition, here With that\nWastes its green rankness on one common heap.\nTherefore if I have been with those, who wail\nTheir avarice, to cleanse me, through reverse\nOf their transgression, such ");
                
        
                struct disk_t* disk = disk_open_from_file("subtract_fat12_volume.img");
                test_error(disk != NULL, "Funkcja disk_open_from_file() niepoprawnie otworzyła plik");
                onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)
        
                struct volume_t* volume = fat_open(disk, 0);
                test_error(volume != NULL, "Funkcja fat_open() niepoprawnie otworzyła wolumin");
                onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)
        
                struct file_t* file = file_open(volume, "WHO.TX");
                test_error(file != NULL, "Funkcja file_open() niepoprawnie otworzyła plik");
                onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)
        
                size_t size = file_read(filecontent, 1, 3647, file);
                test_error(size == 3647, "Funkcja file_read() niepoprawnie wczytała dane z pliku, powinna wczytać 3647 bajtów, a wczytała %lu", size);
                onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)

                int diff_pos = mem_find_first_difference(filecontent, expected_filecontent, 3647);
            
                // jeśli jest, to raportuj błąd
                test_error(diff_pos == -1, "Dane wczytane z pliku nie są poprawne; różnica w bajcie %d; jest 0x%02x a powinno być 0x%02x",
                    diff_pos, mem_get_byte(filecontent, diff_pos), mem_get_byte(expected_filecontent, diff_pos));
            
                onerror_compare_memory(expected_filecontent, filecontent, 3647);


                free(filecontent);
        
                file_close(file);
                fat_close(volume);
                disk_close(disk);
        
                test_no_heap_leakage();
                onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)
            
    //
    // -----------
    //

    // przywrócenie podstawowych parametów przydzielania zasobów (jeśli to tylko możliwe)
    rldebug_reset_limits();
    test_file_write_limit_restore();
    
    test_ok();
}

//
//  Test 11: Sprawdzanie poprawności działania funkcji file_read
//
void UTEST11(void)
{
    // informacje o teście
    test_start(11, "Sprawdzanie poprawności działania funkcji file_read", __LINE__);

    // uwarunkowanie zasobów - pamięci, itd...
    test_file_write_limit_setup(33554432);
    rldebug_reset_limits();
    
    //
    // -----------
    //
    
        
                char *filecontent = (char *)calloc(1536, 1);
                char expected_filecontent[1537] = "";
        
                strcat(expected_filecontent, "       And silent as the moon, &c\nThe same metaphor will recur, Canto V. v. 29.\n        Into a place I came\n       Where light was silent all.\n\nv. 65.  When the power of Julius.] This is explained by the\ncommentators to mean \"Although it was rather late with respect to\nmy birth before Julius Caesar assumed the supreme authority, and\nmade himself perpetual dictator.\"\n\nv. 98.  That greyhound.]  This passage is intended as an eulogium\non the liberal spirit of his Veronese patron Can Grande della\nScala.\n\nv. 102.  \'Twizt either Feltro.]  Verona, the country of Can della\nScala, is situated between Feltro, a city in the Marca\nTrivigiana, and Monte Feltro, a city in the territory of Urbino.\n\nv. 103.  Italia\'s plains.]  \"Umile Italia,\" from Virgil, Aen lib.\niii. 522.\n        Humilemque videmus\n       Italiam.\n\nv. 115.  Content in fire.]  The spirits in Purgatory.\n\nv. 118.  A spirit worthier.]  Beatrice, who conducts the Poet\nthrough Paradise.\n\nv. 130.  Saint Peter\'s gate.]  The gate of Purgatory, which the\nPoet feigns to be guarded by an angel placed on that station by\nSt. Peter.\n\nCANTO II\n\nv. 1.  Now was the day.]  A compendium of Virgil\'s description\nAen. lib. iv 522.  Nox erat, &c. Compare Apollonius Rhodius, lib\niii. 744, and lib. iv. 1058\n\nv. 8.  O mind.]\n        O thought that write all that I met,\n        And in the tresorie it set\n        Of my braine, now shall men see\n        If any virtue in thee be.\n               Chaucer.  Temple of Fame, b. ii. v.18\n\nv. 14.  Silvius\'sire.] Aeneas.\n\nv. 30.  The chosen vesse");
                
        
                struct disk_t* disk = disk_open_from_file("subtract_fat12_volume.img");
                test_error(disk != NULL, "Funkcja disk_open_from_file() niepoprawnie otworzyła plik");
                onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)
        
                struct volume_t* volume = fat_open(disk, 0);
                test_error(volume != NULL, "Funkcja fat_open() niepoprawnie otworzyła wolumin");
                onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)
        
                struct file_t* file = file_open(volume, "AIR.BIN");
                test_error(file != NULL, "Funkcja file_open() niepoprawnie otworzyła plik");
                onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)
        
                size_t size = file_read(filecontent, 1, 1536, file);
                test_error(size == 1536, "Funkcja file_read() niepoprawnie wczytała dane z pliku, powinna wczytać 1536 bajtów, a wczytała %lu", size);
                onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)

                int diff_pos = mem_find_first_difference(filecontent, expected_filecontent, 1536);
            
                // jeśli jest, to raportuj błąd
                test_error(diff_pos == -1, "Dane wczytane z pliku nie są poprawne; różnica w bajcie %d; jest 0x%02x a powinno być 0x%02x",
                    diff_pos, mem_get_byte(filecontent, diff_pos), mem_get_byte(expected_filecontent, diff_pos));
            
                onerror_compare_memory(expected_filecontent, filecontent, 1536);


                free(filecontent);
        
                file_close(file);
                fat_close(volume);
                disk_close(disk);
        
                test_no_heap_leakage();
                onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)
            
    //
    // -----------
    //

    // przywrócenie podstawowych parametów przydzielania zasobów (jeśli to tylko możliwe)
    rldebug_reset_limits();
    test_file_write_limit_restore();
    
    test_ok();
}

//
//  Test 12: Sprawdzanie poprawności działania funkcji file_read
//
void UTEST12(void)
{
    // informacje o teście
    test_start(12, "Sprawdzanie poprawności działania funkcji file_read", __LINE__);

    // uwarunkowanie zasobów - pamięci, itd...
    test_file_write_limit_setup(33554432);
    rldebug_reset_limits();
    
    //
    // -----------
    //
    
        
                char *filecontent = (char *)calloc(286, 1);
                char expected_filecontent[287] = "";
        
                strcat(expected_filecontent, "nto the tears,\nWith which I hasten that whereof thou spak\'st.\nI have on earth a kinswoman; her name\nAlagia, worthy in herself, so ill\nExample of our house corrupt her not:\nAnd she is all remaineth of me there.\"\n\n\n\nCANTO XX\n\nIll strives the will, \'gainst will more wise that strives\nHis ");
                
        
                struct disk_t* disk = disk_open_from_file("subtract_fat12_volume.img");
                test_error(disk != NULL, "Funkcja disk_open_from_file() niepoprawnie otworzyła plik");
                onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)
        
                struct volume_t* volume = fat_open(disk, 0);
                test_error(volume != NULL, "Funkcja fat_open() niepoprawnie otworzyła wolumin");
                onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)
        
                struct file_t* file = file_open(volume, "FORM.BIN");
                test_error(file != NULL, "Funkcja file_open() niepoprawnie otworzyła plik");
                onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)
        
                size_t size = file_read(filecontent, 1, 286, file);
                test_error(size == 286, "Funkcja file_read() niepoprawnie wczytała dane z pliku, powinna wczytać 286 bajtów, a wczytała %lu", size);
                onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)

                int diff_pos = mem_find_first_difference(filecontent, expected_filecontent, 286);
            
                // jeśli jest, to raportuj błąd
                test_error(diff_pos == -1, "Dane wczytane z pliku nie są poprawne; różnica w bajcie %d; jest 0x%02x a powinno być 0x%02x",
                    diff_pos, mem_get_byte(filecontent, diff_pos), mem_get_byte(expected_filecontent, diff_pos));
            
                onerror_compare_memory(expected_filecontent, filecontent, 286);


                free(filecontent);
        
                file_close(file);
                fat_close(volume);
                disk_close(disk);
        
                test_no_heap_leakage();
                onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)
            
    //
    // -----------
    //

    // przywrócenie podstawowych parametów przydzielania zasobów (jeśli to tylko możliwe)
    rldebug_reset_limits();
    test_file_write_limit_restore();
    
    test_ok();
}

//
//  Test 13: Sprawdzanie poprawności działania funkcji file_read
//
void UTEST13(void)
{
    // informacje o teście
    test_start(13, "Sprawdzanie poprawności działania funkcji file_read", __LINE__);

    // uwarunkowanie zasobów - pamięci, itd...
    test_file_write_limit_setup(33554432);
    rldebug_reset_limits();
    
    //
    // -----------
    //
    

                char *filecontent = (char *)calloc(3421, 1);
                char expected_filecontent[3422] = "";

                strcat(expected_filecontent, "His wings are pointed, for there always throng\nAll such as not to Archeron descend.\"\n     Then I: \"If new laws have not quite destroy\'d\nMemory and use of that sweet song of love,\nThat while all my cares had power to \'swage;\nPlease thee with it a little to console\nMy spirit, that incumber\'d with its frame,\nTravelling so far, of pain is overcome.\"\n     \"Love that discourses in my thoughts.\"  He then\nBegan in such soft accents, that within\nThe sweetness thrills me yet.  My gentle guide\nAnd all who came with him, so well were pleas\'d,\nThat seem\'d naught else might in their thoughts have room.\n     Fast fix\'d in mute attention to his notes\nWe stood, when lo!  that old man venerable\nExclaiming, \"How is this, ye tardy spirits?\nWhat negligence detains you loit\'ring here?\nRun to the mountain to cast off those scales,\nThat from your eyes the sight of God conceal.\"\n     As a wild flock of pigeons, to their food\nCollected, blade or tares, without their pride\nAccustom\'d, and in still and quiet sort,\nIf aught alarm them, suddenly desert\nTheir meal, assail\'d by more important care;\nSo I that new-come troop beheld, the song\nDeserting, hasten to the mountain\'s side,\nAs one who goes yet where he tends knows not.\n     Nor with less hurried step did we depart.\n\n\n\nCANTO III\n\nThem sudden flight had scatter\'d over the plain,\nTurn\'d tow\'rds the mountain, whither reason\'s voice\nDrives us; I to my faithful company\nAdhering, left it not.  For how of him\nDepriv\'d, might I have sped, or who beside\nWould o\'er the mountainous tract have led my steps\nHe with the bitter pang of self-remorse\nSeem\'d smitten.  O clear conscience and upright\nHow doth a little fling wound thee sore!\n     Soon as his feet desisted (slack\'ning pace),\nFrom haste, that mars all decency of act,\nMy mind, that in itself before was wrapt,\nIts thoughts expanded, as with joy restor\'d:\nAnd full against the steep ascent I set\nMy face, where highest to heav\'n its top o\'erflows.\n     The sun, that flar\'d behind, with ruddy beam\nBefore my form was broken; for in me\nHis rays resistance met.  I turn\'d aside\nWith fear of being left, when I beheld\nOnly before myself the ground obscur\'d.\nWhen thus my solace, turning him around,\nBespake me kindly:  \"Why distrustest thou?\nBeliev\'st not I am with thee, thy sure guide?\nIt now is evening there, where buried lies\nThe body, in which I cast a shade, remov\'d\nTo Naples from Brundusium\'s wall.  Nor thou\nMarvel, if before me no shadow fall,\nMore than that in the sky element\nOne ray obstructs not other.  To endure\nTorments of heat and cold extreme, like frames\nThat virtue hath dispos\'d, which how it works\nWills not to us should be reveal\'d.  Insane\nWho hopes, our reason may that space explore,\nWhich holds three persons in one substance knit.\nSeek not the wherefore, race of human kind;\nCould ye have seen the whole, no need had been\nFor Mary to bring forth.  Moreover ye\nHave seen such men desiring fruitlessly;\nTo whose desires repose would have been giv\'n,\nThat now but serve them for eternal grief.\nI speak of Plato, and the Stagyrite,\nAnd others many more.\"  And then he bent\nDownwards his forehead, and in troubled mood\nBroke off his speech.  Meanwhile we had arriv\'d\nFar as the mountain\'s foot, and there the rock\nFound of so steep ascent, that nimblest steps\nTo climb it had been vain.  The most remote\nMost wild untrodden path, in all the tract\n\'Twixt Lerice and Turbia were to this\nA ladder easy\' an");

                struct disk_t* disk = disk_open_from_file("subtract_fat12_volume.img");
                test_error(disk != NULL, "Funkcja disk_open_from_file() niepoprawnie otworzyła plik");
                onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)

                struct volume_t* volume = fat_open(disk, 0);
                test_error(volume != NULL, "Funkcja fat_open() niepoprawnie otworzyła wolumin");
                onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)

                struct file_t* file = file_open(volume, "TAIL");
                test_error(file != NULL, "Funkcja file_open() niepoprawnie otworzyła plik");
                onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)

                size_t size = file_read(filecontent, 1, 3648, file);
                test_error(size == 3421, "Funkcja file_read() niepoprawnie wczytała dane z pliku, powinna wczytać 3421 bajtów, a wczytała %lu", size);
                onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)

                int diff_pos = mem_find_first_difference(filecontent, expected_filecontent, 3421);

                // jeśli jest, to raportuj błąd
                test_error(diff_pos == -1, "Dane wczytane z pliku nie są poprawne; różnica w bajcie %d; jest 0x%02x a powinno być 0x%02x",
                    diff_pos, mem_get_byte(filecontent, diff_pos), mem_get_byte(expected_filecontent, diff_pos));

                onerror_compare_memory(expected_filecontent, filecontent, 3421);


                free(filecontent);

                file_close(file);
                fat_close(volume);
                disk_close(disk);

                test_no_heap_leakage();
                onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)
            
    //
    // -----------
    //

    // przywrócenie podstawowych parametów przydzielania zasobów (jeśli to tylko możliwe)
    rldebug_reset_limits();
    test_file_write_limit_restore();
    
    test_ok();
}

//
//  Test 14: Sprawdzanie poprawności działania funkcji file_read
//
void UTEST14(void)
{
    // informacje o teście
    test_start(14, "Sprawdzanie poprawności działania funkcji file_read", __LINE__);

    // uwarunkowanie zasobów - pamięci, itd...
    test_file_write_limit_setup(33554432);
    rldebug_reset_limits();
    
    //
    // -----------
    //
    

                char *filecontent = (char *)calloc(3749, 1);
                char expected_filecontent[3750] = "";

                strcat(expected_filecontent, "seaport on the\nconfines of the Maremma, has led them to conceive hopes of\nbecoming a naval power: but this scheme will prove as chimerical\nas their former plan for the discovery of a subterraneous stream\nunder their city.\"  Why they gave the appellation of Diana to the\nimagined stream, Venturi says he leaves it to the antiquaries of\nSienna to conjecture.\n\nCANTO XIV\n\nv. 34.  Maim\'d of Pelorus.]  Virg. Aen. 1. iii. 414.\n\n--a hill\nTorn from Pelorus\nMilton P. L. b. i. 232\n\nv. 45.  \'Midst brute swine.]  The people of Casentino.\n\nv. 49.  Curs.]  The Arno leaves Arezzo about four miles to the\nleft.\n\nv. 53.  Wolves.]  The Florentines.\n\nv. 55.  Foxes.]  The Pisans\n\nv. 61.  Thy grandson.]  Fulcieri de\' Calboli, grandson of\nRinieri de\' Calboli, who is here spoken to.  The atrocities\npredicted came to pass in 1302.  See G. Villani, 1.  viii c. 59\n\nv. 95.  \'Twixt Po, the mount, the Reno, and the shore.]  The\nboundaries of Romagna.\n\nv. 99.  Lizio.]  Lizio da Valbona, introduced into Boccaccio\'s\nDecameron, G. v. N, 4.\n\nv. 100.  Manardi, Traversaro, and Carpigna.1 Arrigo Manardi of\nFaenza, or as some say, of Brettinoro, Pier Traversaro, lord of\nRavenna, and Guido di Carpigna of Montefeltro.\n\nv. 102.  In Bologna the low artisan.]  One who had been a\nmechanic named Lambertaccio, arrived at almost supreme power in\nBologna.\n\nv. 103.  Yon Bernardin.]  Bernardin di Fosco, a man of low\norigin but great talents, who governed at Faenza.\n\nv. 107.  Prata.]  A place between Faenza and Ravenna\n\nv. 107.  Of Azzo him.] Ugolino of the Ubaldini family in Tuscany\nHe is recounted among the poets by Crescimbeni and Tiraboschi.\n\nv. 108.  Tignoso.] Federigo Tignoso of Rimini.\n\nv. 109.  Traversaro\'s house and Anastagio\'s.]  Two noble families\nof Ravenna.  She to whom Dryden has given the name of Honoria, in\nthe fable so admirably paraphrased from Boccaccio, was of the\nformer: her lover and the specter were of the Anastagi family.\n\nv. 111.  The ladies, &c.]  These two lines express the true\nspirit of chivalry.  \"Agi\" is understood by the commentators whom\nI have consulted,to mean \"the ease procured for others by the\nexertions of knight-errantry.\"  But surely it signifies the\nalternation of ease with labour.\n\nv. 114.  O Brettinoro.]  A beautifully situated castle in\nRomagna, the hospitable residence of Guido del Duca, who is here\nspeaking.\n\nv. 118.  Baynacavallo.]  A castle between Imola and Ravenna\n\nv. 118.  Castracaro ill\nAnd Conio worse.]  Both in Romagna.\n\nv. 121.  Pagani.]  The Pagani were lords of Faenza and Imola. One\nof them Machinardo, was named the Demon, from his treachery.\nSee Hell, Canto XXVII. 47, and Note.\n\nv. 124.  Hugolin.]  Ugolino Ubaldini, a noble and virtuous person\nin Faenza, who, on account of his age probably, was not likely to\nleave any offspring behind him.  He is enumerated among the poets\nby Crescimbeni, and Tiraboschi.  Mr. Matthias\'s edit. vol. i. 143\n\nv. 136.  Whosoever finds Will slay me.] The words of Cain, Gen.\ne. iv. 14.\n\nv. 142.  Aglauros.]  Ovid, Met.  I, ii.  fate. 12.\n\nv. 145.  There was the galling bit.]  Referring to what had been\nbefore said, Canto XIII.  35.\n\nCANTO XV\n\nv. 1.  As much.]  It wanted three hours of sunset.\n\nv. 16.  As when the ray.]  Compare Virg. Aen. 1.viii. 22, and\nApol. Rhod. 1. iii. 755.\n\nv. 19.  Ascending at a glance.]  Lucretius, 1. iv. 215.\n\nv. 20.  Differs from the stone.]  The motion of light being\nquicker  than that of a stone through an equal space.\n\nv. 38.  Blessed the merciful.  Matt. c. v. 7.\n\nv. 43.  Romagna\'s spirit.] Guido del Duea, of Brettinoro whom we\nhave seen in the preceding Canto.\n\nv. 87.  A dame.]  Luke, c. ii.  18\n\nv. 101.  How shall we those requite.]  The answer of Pisistratus\nthe tyrant to his wife, when she urged him to inflict the\npun");

                struct disk_t* disk = disk_open_from_file("subtract_fat12_volume.img");
                test_error(disk != NULL, "Funkcja disk_open_from_file() niepoprawnie otworzyła plik");
                onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)

                struct volume_t* volume = fat_open(disk, 0);
                test_error(volume != NULL, "Funkcja fat_open() niepoprawnie otworzyła wolumin");
                onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)

                struct file_t* file = file_open(volume, "MULTIPLY.BIN");
                test_error(file != NULL, "Funkcja file_open() niepoprawnie otworzyła plik");
                onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)

                size_t size = file_read(filecontent, 1, 4131, file);
                test_error(size == 3749, "Funkcja file_read() niepoprawnie wczytała dane z pliku, powinna wczytać 3749 bajtów, a wczytała %lu", size);
                onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)

                int diff_pos = mem_find_first_difference(filecontent, expected_filecontent, 3749);

                // jeśli jest, to raportuj błąd
                test_error(diff_pos == -1, "Dane wczytane z pliku nie są poprawne; różnica w bajcie %d; jest 0x%02x a powinno być 0x%02x",
                    diff_pos, mem_get_byte(filecontent, diff_pos), mem_get_byte(expected_filecontent, diff_pos));

                onerror_compare_memory(expected_filecontent, filecontent, 3749);


                free(filecontent);

                file_close(file);
                fat_close(volume);
                disk_close(disk);

                test_no_heap_leakage();
                onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)
            
    //
    // -----------
    //

    // przywrócenie podstawowych parametów przydzielania zasobów (jeśli to tylko możliwe)
    rldebug_reset_limits();
    test_file_write_limit_restore();
    
    test_ok();
}

//
//  Test 15: Sprawdzanie poprawności działania funkcji file_read
//
void UTEST15(void)
{
    // informacje o teście
    test_start(15, "Sprawdzanie poprawności działania funkcji file_read", __LINE__);

    // uwarunkowanie zasobów - pamięci, itd...
    test_file_write_limit_setup(33554432);
    rldebug_reset_limits();
    
    //
    // -----------
    //
    

                char *filecontent = (char *)calloc(3364, 1);
                char expected_filecontent[3365] = "";

                strcat(expected_filecontent, "wond\'ring and suspense,\nReplied:  \"I see that thou believ\'st these things,\nBecause I tell them, but discern\'st not how;\nSo that thy knowledge waits not on thy faith:\nAs one who knows the name of thing by rote,\nBut is a stranger to its properties,\nTill other\'s tongue reveal them.  Fervent love\nAnd lively hope with violence assail\nThe kingdom of the heavens, and overcome\nThe will of the Most high; not in such sort\nAs man prevails o\'er man; but conquers it,\nBecause \'t is willing to be conquer\'d, still,\nThough conquer\'d, by its mercy conquering.\n     \"Those, in the eye who live the first and fifth,\nCause thee to marvel, in that thou behold\'st\nThe region of the angels deck\'d with them.\nThey quitted not their bodies, as thou deem\'st,\nGentiles but Christians, in firm rooted faith,\nThis of the feet in future to be pierc\'d,\nThat of feet nail\'d already to the cross.\nOne from the barrier of the dark abyss,\nWhere never any with good will returns,\nCame back unto his bones.  Of lively hope\nSuch was the meed; of lively hope, that wing\'d\nThe prayers sent up to God for his release,\nAnd put power into them to bend his will.\nThe glorious Spirit, of whom I speak to thee,\nA little while returning to the flesh,\nBeliev\'d in him, who had the means to help,\nAnd, in believing, nourish\'d such a flame\nOf holy love, that at the second death\nHe was made sharer in our gamesome mirth.\nThe other, through the riches of that grace,\nWhich from so deep a fountain doth distil,\nAs never eye created saw its rising,\nPlac\'d all his love below on just and right:\nWherefore of grace God op\'d in him the eye\nTo the redemption of mankind to come;\nWherein believing, he endur\'d no more\nThe filth of paganism, and for their ways\nRebuk\'d the stubborn nations.  The three nymphs,\nWhom at the right wheel thou beheldst advancing,\nWere sponsors for him more than thousand years\nBefore baptizing.  O how far remov\'d,\nPredestination!  is thy root from such\nAs see not the First cause entire: and ye,\nO mortal men!  be wary how ye judge:\nFor we, who see our Maker, know not yet\nThe number of the chosen: and esteem\nSuch scantiness of knowledge our delight:\nFor all our good is in that primal good\nConcentrate, and God\'s will and ours are one.\"\n     So, by that form divine, was giv\'n to me\nSweet medicine to clear and strengthen sight,\nAnd, as one handling skillfully the harp,\nAttendant on some skilful songster\'s voice\nBids the chords vibrate, and therein the song\nAcquires more pleasure; so, the whilst it spake,\nIt doth remember me, that I beheld\nThe pair of blessed luminaries move.\nLike the accordant twinkling of two eyes,\nTheir beamy circlets, dancing to the sounds.\n\n\n\nCANTO XXI\n\nAgain mine eyes were fix\'d on Beatrice,\nAnd with mine eyes my soul, that in her looks\nFound all contentment.  Yet no smile she wore\nAnd, \"Did I smile,\" quoth she, \"thou wouldst be straight\nLike Semele when into ashes turn\'d:\nFor, mounting these eternal palace-stairs,\nMy beauty, which the loftier it climbs,\nAs thou hast noted, still doth kindle more,\nSo shines, that, were no temp\'ring interpos\'d,\nThy mortal puissance would from its rays\nShrink, as the leaf doth from the thunderbolt.\nInto the seventh splendour are we wafted,\nThat underneath the burning lion\'s breast\nBeams, in this hour, commingled with his might,\nThy mind be with thine eyes: and in them mirror\'d\nThe shape, which in this mirror sha");

                struct disk_t* disk = disk_open_from_file("subtract_fat12_volume.img");
                test_error(disk != NULL, "Funkcja disk_open_from_file() niepoprawnie otworzyła plik");
                onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)

                struct volume_t* volume = fat_open(disk, 0);
                test_error(volume != NULL, "Funkcja fat_open() niepoprawnie otworzyła wolumin");
                onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)

                struct file_t* file = file_open(volume, "THOUSAND.TXT");
                test_error(file != NULL, "Funkcja file_open() niepoprawnie otworzyła plik");
                onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)

                size_t size = file_read(filecontent, 1, 3672, file);
                test_error(size == 3364, "Funkcja file_read() niepoprawnie wczytała dane z pliku, powinna wczytać 3364 bajtów, a wczytała %lu", size);
                onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)

                int diff_pos = mem_find_first_difference(filecontent, expected_filecontent, 3364);

                // jeśli jest, to raportuj błąd
                test_error(diff_pos == -1, "Dane wczytane z pliku nie są poprawne; różnica w bajcie %d; jest 0x%02x a powinno być 0x%02x",
                    diff_pos, mem_get_byte(filecontent, diff_pos), mem_get_byte(expected_filecontent, diff_pos));

                onerror_compare_memory(expected_filecontent, filecontent, 3364);


                free(filecontent);

                file_close(file);
                fat_close(volume);
                disk_close(disk);

                test_no_heap_leakage();
                onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)
            
    //
    // -----------
    //

    // przywrócenie podstawowych parametów przydzielania zasobów (jeśli to tylko możliwe)
    rldebug_reset_limits();
    test_file_write_limit_restore();
    
    test_ok();
}

//
//  Test 16: Sprawdzanie poprawności działania funkcji file_read
//
void UTEST16(void)
{
    // informacje o teście
    test_start(16, "Sprawdzanie poprawności działania funkcji file_read", __LINE__);

    // uwarunkowanie zasobów - pamięci, itd...
    test_file_write_limit_setup(33554432);
    rldebug_reset_limits();
    
    //
    // -----------
    //
    

                char *filecontent = (char *)calloc(3027, 1);
                char expected_filecontent[3028] = "";

                strcat(expected_filecontent, "onferred by that family on our poet at a subsequent perid of his\nexile in 1307.\n\n\n\nCanto XXV\n\nv.1.  The sinner ]  So Trissino\n        Poi facea con le man le fiche al cielo\n        Dicendo:  Togli, Iddio; che puoi piu farmi?\n               L\'ital. Lib. c. xii\n\nv. 12.  Thy seed]  Thy ancestry.\n\nv. 15.  Not him]  Capanaeus.  Canto XIV.\n\nv. 18.  On Marenna\'s marsh.]  An extensive tract near the\nsea-shore in Tuscany.\n\nv. 24.  Cacus.]  Virgil, Aen. l. viii. 193.\n\nv. 31.  A hundred blows.]  Less than ten blows, out of the\nhundred Hercules gave him, deprived him of feeling.\n\nv. 39.  Cianfa]  He is said to have been of the family of Donati\nat Florence.\n\nv. 57.  Thus up the shrinking paper.]\n        --All my bowels crumble up to dust.\n        I am a scribbled form, drawn up with a pen\n        Upon a parchment; and against this fire\n        Do I shrink up.\n               Shakespeare, K. John, a. v. s. 7.\n\nv. 61.  Agnello.]  Agnello Brunelleschi\n\nv. 77.  In that part.]  The navel.\n\nv. 81.  As if by sleep or fev\'rous fit assail\'d.]\n               O Rome!  thy head\n        Is drown\'d in sleep, and all thy body fev\'ry.\n               Ben Jonson\'s Catiline.\n\nv. 85.  Lucan.]  Phars. l. ix. 766 and 793.\n\nv. 87.  Ovid.] Metam. l. iv. and v.\n\nv. 121.  His sharpen\'d visage.]  Compare Milton, P. L. b. x. 511\n&c.\n\nv. 131.  Buoso.]  He is said to have been of the Donati family.\n\nv. 138.  Sciancato.]  Puccio Sciancato, a noted robber, whose\nfamilly, Venturi says, he has not been able to discover.\n\nv. 140.  Gaville.]  Francesco Guercio Cavalcante was killed at\nGaville, near Florence; and in revenge of his death several\ninhabitants of that district were put to death.\n\nCANTO XXVI\n\nv. 7. But if our minds.]\n\n        Namque sub Auroram, jam dormitante lucerna,\n        Somnia quo cerni tempore vera solent.\n               Ovid, Epist. xix\n\nThe same poetical superstition is alluded to in the Purgatory,\nCant. IX. and XXVII.\n\nv. 9. Shall feel what Prato.]  The poet prognosticates the\ncalamities which were soon to befal his native city, and which he\nsays, even her nearest neighbor, Prato, would wish her.  The\ncalamities more particularly pointed at, are said to be the fall\nof a wooden bridge over the Arno, in May, 1304, where a large\nmultitude were assembled to witness a representation  of hell nnd\nthe infernal torments, in consequence of which accident many\nlives were lost; and a conflagration that in the following month\ndestroyed more than seventeen hundred houses, many ofthem\nsumptuous buildings.  See G. Villani, Hist. l. viii. c. 70 and\n71.\n\nv. 22.  More than I am wont.]  \"When I reflect on the punishment\nallotted to those who do not give sincere and upright advice to\nothers I am more anxious than ever not to abuse to so bad a\npurpose those talents, whatever they may be, which Nature, or\nrather Providence, has conferred on me.\"  It is probable that\nthis declaration was the result of real feeling Textd have\ngiven great weight to\nany opinion or party he had espoused, and to whom indigence and\nexile might h");

                struct disk_t* disk = disk_open_from_file("subtract_fat12_volume.img");
                test_error(disk != NULL, "Funkcja disk_open_from_file() niepoprawnie otworzyła plik");
                onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)

                struct volume_t* volume = fat_open(disk, 0);
                test_error(volume != NULL, "Funkcja fat_open() niepoprawnie otworzyła wolumin");
                onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)

                struct file_t* file = file_open(volume, "LIFE");
                test_error(file != NULL, "Funkcja file_open() niepoprawnie otworzyła plik");
                onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)

                size_t size = file_read(filecontent, 1, 3239, file);
                test_error(size == 3027, "Funkcja file_read() niepoprawnie wczytała dane z pliku, powinna wczytać 3027 bajtów, a wczytała %lu", size);
                onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)

                int diff_pos = mem_find_first_difference(filecontent, expected_filecontent, 3027);

                // jeśli jest, to raportuj błąd
                test_error(diff_pos == -1, "Dane wczytane z pliku nie są poprawne; różnica w bajcie %d; jest 0x%02x a powinno być 0x%02x",
                    diff_pos, mem_get_byte(filecontent, diff_pos), mem_get_byte(expected_filecontent, diff_pos));

                onerror_compare_memory(expected_filecontent, filecontent, 3027);


                free(filecontent);

                file_close(file);
                fat_close(volume);
                disk_close(disk);

                test_no_heap_leakage();
                onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)
            
    //
    // -----------
    //

    // przywrócenie podstawowych parametów przydzielania zasobów (jeśli to tylko możliwe)
    rldebug_reset_limits();
    test_file_write_limit_restore();
    
    test_ok();
}

//
//  Test 17: Sprawdzanie poprawności działania funkcji file_read
//
void UTEST17(void)
{
    // informacje o teście
    test_start(17, "Sprawdzanie poprawności działania funkcji file_read", __LINE__);

    // uwarunkowanie zasobów - pamięci, itd...
    test_file_write_limit_setup(33554432);
    rldebug_reset_limits();
    
    //
    // -----------
    //
    

                char *filecontent = (char *)calloc(3647, 1);
                char expected_filecontent[3648] = "";

                strcat(expected_filecontent, "nd tears\nFollow so closely on the passion prompts them,\nThey wait not for the motions of the will\nIn natures most sincere.  I did but smile,\nAs one who winks; and thereupon the shade\nBroke off, and peer\'d into mine eyes, where best\nOur looks interpret. \"So to good event\nMayst thou conduct such great emprize,\" he cried,\n\"Say, why across thy visage beam\'d, but now,\nThe lightning of a smile!\"  On either part\nNow am I straiten\'d; one conjures me speak,\nTh\' other to silence binds me: whence a sigh\nI utter, and the sigh is heard.  \"Speak on; \"\nThe teacher cried;  \"and do not fear to speak,\nBut tell him what so earnestly he asks.\"\nWhereon I thus:  \"Perchance, O ancient spirit!\nThou marvel\'st at my smiling. There is room\nFor yet more wonder.  He who guides my ken\nOn high, he is that Mantuan, led by whom\nThou didst presume of men arid gods to sing.\nIf other cause thou deem\'dst for which I smil\'d,\nLeave it as not the true one; and believe\nThose words, thou spak\'st of him, indeed the cause.\"\n     Now down he bent t\' embrace my teacher\'s feet;\nBut he forbade him:  \"Brother!  do it not:\nThou art a shadow, and behold\'st a shade.\"\nHe rising answer\'d thus:  \"Now hast thou prov\'d\nThe force and ardour of the love I bear thee,\nWhen I forget we are but things of air,\nAnd as a substance treat an empty shade.\"\n\n\n\nCANTO XXII\n\nNow we had left the angel, who had turn\'d\nTo the sixth circle our ascending step,\nOne gash from off my forehead raz\'d: while they,\nWhose wishes tend to justice, shouted forth:\n\"Blessed!\"  and ended with, \"I thirst:\" and I,\nMore nimble than along the other straits,\nSo journey\'d, that, without the sense of toil,\nI follow\'d upward the swift-footed shades;\nWhen Virgil thus began:  \"Let its pure flame\nFrom virtue flow, and love can never fail\nTo warm another\'s bosom\' so the light\nShine manifestly forth.  Hence from that hour,\nWhen \'mongst us in the purlieus of the deep,\nCame down the spirit of Aquinum\'s hard,\nWho told of thine affection, my good will\nHath been for thee of quality as strong\nAs ever link\'d itself to one not seen.\nTherefore these stairs will now seem short to me.\nBut tell me: and if too secure I loose\nThe rein with a friend\'s license, as a friend\nForgive me, and speak now as with a friend:\nHow chanc\'d it covetous desire could find\nPlace in that bosom, \'midst such ample store\nOf wisdom, as thy zeal had treasur\'d there?\"\n     First somewhat mov\'d to laughter by his words,\nStatius replied: \"Each syllable of thine\nIs a dear pledge of love.  Things oft appear\nThat minister false matters to our doubts,\nWhen their true causes are remov\'d from sight.\nThy question doth assure me, thou believ\'st\nI was on earth a covetous man, perhaps\nBecause thou found\'st me in that circle plac\'d.\nKnow then I was too wide of avarice:\nAnd e\'en for that excess, thousands of moons\nHave wax\'d and wan\'d upon my sufferings.\nAnd were it not that I with heedful care\nNoted where thou exclaim\'st as if in ire\nWith human nature, \'Why, thou cursed thirst\nOf gold!  dost not with juster measure guide\nThe appetite of mortals?\'  I had met\nThe fierce encounter of the voluble rock.\nThen was I ware that with too ample wing\nThe hands may haste to lavishment, and turn\'d,\nAs from my other evil, so from this\nIn penitence.  How many from their grave\nShall with shorn locks arise, who living, aye\nAnd at life\'s last extreme, of this offence,\nThrough ignorance, did not repent.  And know,\nThe fault which lies direct from any sin\nIn level opposition, here With that\nWastes its green rankness on one common heap.\nTherefore if I have been with those, who wail\nTheir avarice, to cleanse me, through reverse\nOf their transgression, such ");

                struct disk_t* disk = disk_open_from_file("subtract_fat12_volume.img");
                test_error(disk != NULL, "Funkcja disk_open_from_file() niepoprawnie otworzyła plik");
                onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)

                struct volume_t* volume = fat_open(disk, 0);
                test_error(volume != NULL, "Funkcja fat_open() niepoprawnie otworzyła wolumin");
                onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)

                struct file_t* file = file_open(volume, "WHO.TX");
                test_error(file != NULL, "Funkcja file_open() niepoprawnie otworzyła plik");
                onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)

                size_t size = file_read(filecontent, 1, 3782, file);
                test_error(size == 3647, "Funkcja file_read() niepoprawnie wczytała dane z pliku, powinna wczytać 3647 bajtów, a wczytała %lu", size);
                onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)

                int diff_pos = mem_find_first_difference(filecontent, expected_filecontent, 3647);

                // jeśli jest, to raportuj błąd
                test_error(diff_pos == -1, "Dane wczytane z pliku nie są poprawne; różnica w bajcie %d; jest 0x%02x a powinno być 0x%02x",
                    diff_pos, mem_get_byte(filecontent, diff_pos), mem_get_byte(expected_filecontent, diff_pos));

                onerror_compare_memory(expected_filecontent, filecontent, 3647);


                free(filecontent);

                file_close(file);
                fat_close(volume);
                disk_close(disk);

                test_no_heap_leakage();
                onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)
            
    //
    // -----------
    //

    // przywrócenie podstawowych parametów przydzielania zasobów (jeśli to tylko możliwe)
    rldebug_reset_limits();
    test_file_write_limit_restore();
    
    test_ok();
}

//
//  Test 18: Sprawdzanie poprawności działania funkcji file_read
//
void UTEST18(void)
{
    // informacje o teście
    test_start(18, "Sprawdzanie poprawności działania funkcji file_read", __LINE__);

    // uwarunkowanie zasobów - pamięci, itd...
    test_file_write_limit_setup(33554432);
    rldebug_reset_limits();
    
    //
    // -----------
    //
    

                char *filecontent = (char *)calloc(1536, 1);
                char expected_filecontent[1537] = "";

                strcat(expected_filecontent, "       And silent as the moon, &c\nThe same metaphor will recur, Canto V. v. 29.\n        Into a place I came\n       Where light was silent all.\n\nv. 65.  When the power of Julius.] This is explained by the\ncommentators to mean \"Although it was rather late with respect to\nmy birth before Julius Caesar assumed the supreme authority, and\nmade himself perpetual dictator.\"\n\nv. 98.  That greyhound.]  This passage is intended as an eulogium\non the liberal spirit of his Veronese patron Can Grande della\nScala.\n\nv. 102.  \'Twizt either Feltro.]  Verona, the country of Can della\nScala, is situated between Feltro, a city in the Marca\nTrivigiana, and Monte Feltro, a city in the territory of Urbino.\n\nv. 103.  Italia\'s plains.]  \"Umile Italia,\" from Virgil, Aen lib.\niii. 522.\n        Humilemque videmus\n       Italiam.\n\nv. 115.  Content in fire.]  The spirits in Purgatory.\n\nv. 118.  A spirit worthier.]  Beatrice, who conducts the Poet\nthrough Paradise.\n\nv. 130.  Saint Peter\'s gate.]  The gate of Purgatory, which the\nPoet feigns to be guarded by an angel placed on that station by\nSt. Peter.\n\nCANTO II\n\nv. 1.  Now was the day.]  A compendium of Virgil\'s description\nAen. lib. iv 522.  Nox erat, &c. Compare Apollonius Rhodius, lib\niii. 744, and lib. iv. 1058\n\nv. 8.  O mind.]\n        O thought that write all that I met,\n        And in the tresorie it set\n        Of my braine, now shall men see\n        If any virtue in thee be.\n               Chaucer.  Temple of Fame, b. ii. v.18\n\nv. 14.  Silvius\'sire.] Aeneas.\n\nv. 30.  The chosen vesse");

                struct disk_t* disk = disk_open_from_file("subtract_fat12_volume.img");
                test_error(disk != NULL, "Funkcja disk_open_from_file() niepoprawnie otworzyła plik");
                onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)

                struct volume_t* volume = fat_open(disk, 0);
                test_error(volume != NULL, "Funkcja fat_open() niepoprawnie otworzyła wolumin");
                onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)

                struct file_t* file = file_open(volume, "AIR.BIN");
                test_error(file != NULL, "Funkcja file_open() niepoprawnie otworzyła plik");
                onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)

                size_t size = file_read(filecontent, 1, 1812, file);
                test_error(size == 1536, "Funkcja file_read() niepoprawnie wczytała dane z pliku, powinna wczytać 1536 bajtów, a wczytała %lu", size);
                onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)

                int diff_pos = mem_find_first_difference(filecontent, expected_filecontent, 1536);

                // jeśli jest, to raportuj błąd
                test_error(diff_pos == -1, "Dane wczytane z pliku nie są poprawne; różnica w bajcie %d; jest 0x%02x a powinno być 0x%02x",
                    diff_pos, mem_get_byte(filecontent, diff_pos), mem_get_byte(expected_filecontent, diff_pos));

                onerror_compare_memory(expected_filecontent, filecontent, 1536);


                free(filecontent);

                file_close(file);
                fat_close(volume);
                disk_close(disk);

                test_no_heap_leakage();
                onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)
            
    //
    // -----------
    //

    // przywrócenie podstawowych parametów przydzielania zasobów (jeśli to tylko możliwe)
    rldebug_reset_limits();
    test_file_write_limit_restore();
    
    test_ok();
}

//
//  Test 19: Sprawdzanie poprawności działania funkcji file_read
//
void UTEST19(void)
{
    // informacje o teście
    test_start(19, "Sprawdzanie poprawności działania funkcji file_read", __LINE__);

    // uwarunkowanie zasobów - pamięci, itd...
    test_file_write_limit_setup(33554432);
    rldebug_reset_limits();
    
    //
    // -----------
    //
    

                char *filecontent = (char *)calloc(286, 1);
                char expected_filecontent[287] = "";

                strcat(expected_filecontent, "nto the tears,\nWith which I hasten that whereof thou spak\'st.\nI have on earth a kinswoman; her name\nAlagia, worthy in herself, so ill\nExample of our house corrupt her not:\nAnd she is all remaineth of me there.\"\n\n\n\nCANTO XX\n\nIll strives the will, \'gainst will more wise that strives\nHis ");

                struct disk_t* disk = disk_open_from_file("subtract_fat12_volume.img");
                test_error(disk != NULL, "Funkcja disk_open_from_file() niepoprawnie otworzyła plik");
                onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)

                struct volume_t* volume = fat_open(disk, 0);
                test_error(volume != NULL, "Funkcja fat_open() niepoprawnie otworzyła wolumin");
                onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)

                struct file_t* file = file_open(volume, "FORM.BIN");
                test_error(file != NULL, "Funkcja file_open() niepoprawnie otworzyła plik");
                onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)

                size_t size = file_read(filecontent, 1, 663, file);
                test_error(size == 286, "Funkcja file_read() niepoprawnie wczytała dane z pliku, powinna wczytać 286 bajtów, a wczytała %lu", size);
                onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)

                int diff_pos = mem_find_first_difference(filecontent, expected_filecontent, 286);

                // jeśli jest, to raportuj błąd
                test_error(diff_pos == -1, "Dane wczytane z pliku nie są poprawne; różnica w bajcie %d; jest 0x%02x a powinno być 0x%02x",
                    diff_pos, mem_get_byte(filecontent, diff_pos), mem_get_byte(expected_filecontent, diff_pos));

                onerror_compare_memory(expected_filecontent, filecontent, 286);


                free(filecontent);

                file_close(file);
                fat_close(volume);
                disk_close(disk);

                test_no_heap_leakage();
                onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)
            
    //
    // -----------
    //

    // przywrócenie podstawowych parametów przydzielania zasobów (jeśli to tylko możliwe)
    rldebug_reset_limits();
    test_file_write_limit_restore();
    
    test_ok();
}

//
//  Test 20: Sprawdzanie poprawności działania funkcji file_read
//
void UTEST20(void)
{
    // informacje o teście
    test_start(20, "Sprawdzanie poprawności działania funkcji file_read", __LINE__);

    // uwarunkowanie zasobów - pamięci, itd...
    test_file_write_limit_setup(33554432);
    rldebug_reset_limits();
    
    //
    // -----------
    //
    

                char expected_filecontent[3422] = "";

                strcat(expected_filecontent, "His wings are pointed, for there always throng\nAll such as not to Archeron descend.\"\n     Then I: \"If new laws have not quite destroy\'d\nMemory and use of that sweet song of love,\nThat while all my cares had power to \'swage;\nPlease thee with it a little to console\nMy spirit, that incumber\'d with its frame,\nTravelling so far, of pain is overcome.\"\n     \"Love that discourses in my thoughts.\"  He then\nBegan in such soft accents, that within\nThe sweetness thrills me yet.  My gentle guide\nAnd all who came with him, so well were pleas\'d,\nThat seem\'d naught else might in their thoughts have room.\n     Fast fix\'d in mute attention to his notes\nWe stood, when lo!  that old man venerable\nExclaiming, \"How is this, ye tardy spirits?\nWhat negligence detains you loit\'ring here?\nRun to the mountain to cast off those scales,\nThat from your eyes the sight of God conceal.\"\n     As a wild flock of pigeons, to their food\nCollected, blade or tares, without their pride\nAccustom\'d, and in still and quiet sort,\nIf aught alarm them, suddenly desert\nTheir meal, assail\'d by more important care;\nSo I that new-come troop beheld, the song\nDeserting, hasten to the mountain\'s side,\nAs one who goes yet where he tends knows not.\n     Nor with less hurried step did we depart.\n\n\n\nCANTO III\n\nThem sudden flight had scatter\'d over the plain,\nTurn\'d tow\'rds the mountain, whither reason\'s voice\nDrives us; I to my faithful company\nAdhering, left it not.  For how of him\nDepriv\'d, might I have sped, or who beside\nWould o\'er the mountainous tract have led my steps\nHe with the bitter pang of self-remorse\nSeem\'d smitten.  O clear conscience and upright\nHow doth a little fling wound thee sore!\n     Soon as his feet desisted (slack\'ning pace),\nFrom haste, that mars all decency of act,\nMy mind, that in itself before was wrapt,\nIts thoughts expanded, as with joy restor\'d:\nAnd full against the steep ascent I set\nMy face, where highest to heav\'n its top o\'erflows.\n     The sun, that flar\'d behind, with ruddy beam\nBefore my form was broken; for in me\nHis rays resistance met.  I turn\'d aside\nWith fear of being left, when I beheld\nOnly before myself the ground obscur\'d.\nWhen thus my solace, turning him around,\nBespake me kindly:  \"Why distrustest thou?\nBeliev\'st not I am with thee, thy sure guide?\nIt now is evening there, where buried lies\nThe body, in which I cast a shade, remov\'d\nTo Naples from Brundusium\'s wall.  Nor thou\nMarvel, if before me no shadow fall,\nMore than that in the sky element\nOne ray obstructs not other.  To endure\nTorments of heat and cold extreme, like frames\nThat virtue hath dispos\'d, which how it works\nWills not to us should be reveal\'d.  Insane\nWho hopes, our reason may that space explore,\nWhich holds three persons in one substance knit.\nSeek not the wherefore, race of human kind;\nCould ye have seen the whole, no need had been\nFor Mary to bring forth.  Moreover ye\nHave seen such men desiring fruitlessly;\nTo whose desires repose would have been giv\'n,\nThat now but serve them for eternal grief.\nI speak of Plato, and the Stagyrite,\nAnd others many more.\"  And then he bent\nDownwards his forehead, and in troubled mood\nBroke off his speech.  Meanwhile we had arriv\'d\nFar as the mountain\'s foot, and there the rock\nFound of so steep ascent, that nimblest steps\nTo climb it had been vain.  The most remote\nMost wild untrodden path, in all the tract\n\'Twixt Lerice and Turbia were to this\nA ladder easy\' an");

                struct disk_t* disk = disk_open_from_file("subtract_fat12_volume.img");
                test_error(disk != NULL, "Funkcja disk_open_from_file() niepoprawnie otworzyła plik");
                onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)

                struct volume_t* volume = fat_open(disk, 0);
                test_error(volume != NULL, "Funkcja fat_open() niepoprawnie otworzyła wolumin");
                onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)

                struct file_t* file = file_open(volume, "TAIL");
                test_error(file != NULL, "Funkcja file_open() niepoprawnie otworzyła plik");
                onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)

                for (int i = 0; i < 3421; ++i)
                {
                    char c;
                    int res = file_read(&c, 1, 1, file);
                    test_error(res == 1, "Funkcja file_read() powinna zwrócić wartość 1, a zwróciła %d", res);
                    onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)
                    test_error(c == expected_filecontent[i], "Funkcja file_read() powinna odczytać w kroku %d znak %c, a odczytała znak %c", i, expected_filecontent[i], c);
                }

                char c;
                int res = file_read(&c, 1, 1, file);
                test_error(res == 0, "Funkcja file_read() powinna zwrócić wartość 0, a zwróciła %d", res);

                file_close(file);
                fat_close(volume);
                disk_close(disk);

                test_no_heap_leakage();
                onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)
            
    //
    // -----------
    //

    // przywrócenie podstawowych parametów przydzielania zasobów (jeśli to tylko możliwe)
    rldebug_reset_limits();
    test_file_write_limit_restore();
    
    test_ok();
}

//
//  Test 21: Sprawdzanie poprawności działania funkcji file_read
//
void UTEST21(void)
{
    // informacje o teście
    test_start(21, "Sprawdzanie poprawności działania funkcji file_read", __LINE__);

    // uwarunkowanie zasobów - pamięci, itd...
    test_file_write_limit_setup(33554432);
    rldebug_reset_limits();
    
    //
    // -----------
    //
    

                char expected_filecontent[3750] = "";

                strcat(expected_filecontent, "seaport on the\nconfines of the Maremma, has led them to conceive hopes of\nbecoming a naval power: but this scheme will prove as chimerical\nas their former plan for the discovery of a subterraneous stream\nunder their city.\"  Why they gave the appellation of Diana to the\nimagined stream, Venturi says he leaves it to the antiquaries of\nSienna to conjecture.\n\nCANTO XIV\n\nv. 34.  Maim\'d of Pelorus.]  Virg. Aen. 1. iii. 414.\n\n--a hill\nTorn from Pelorus\nMilton P. L. b. i. 232\n\nv. 45.  \'Midst brute swine.]  The people of Casentino.\n\nv. 49.  Curs.]  The Arno leaves Arezzo about four miles to the\nleft.\n\nv. 53.  Wolves.]  The Florentines.\n\nv. 55.  Foxes.]  The Pisans\n\nv. 61.  Thy grandson.]  Fulcieri de\' Calboli, grandson of\nRinieri de\' Calboli, who is here spoken to.  The atrocities\npredicted came to pass in 1302.  See G. Villani, 1.  viii c. 59\n\nv. 95.  \'Twixt Po, the mount, the Reno, and the shore.]  The\nboundaries of Romagna.\n\nv. 99.  Lizio.]  Lizio da Valbona, introduced into Boccaccio\'s\nDecameron, G. v. N, 4.\n\nv. 100.  Manardi, Traversaro, and Carpigna.1 Arrigo Manardi of\nFaenza, or as some say, of Brettinoro, Pier Traversaro, lord of\nRavenna, and Guido di Carpigna of Montefeltro.\n\nv. 102.  In Bologna the low artisan.]  One who had been a\nmechanic named Lambertaccio, arrived at almost supreme power in\nBologna.\n\nv. 103.  Yon Bernardin.]  Bernardin di Fosco, a man of low\norigin but great talents, who governed at Faenza.\n\nv. 107.  Prata.]  A place between Faenza and Ravenna\n\nv. 107.  Of Azzo him.] Ugolino of the Ubaldini family in Tuscany\nHe is recounted among the poets by Crescimbeni and Tiraboschi.\n\nv. 108.  Tignoso.] Federigo Tignoso of Rimini.\n\nv. 109.  Traversaro\'s house and Anastagio\'s.]  Two noble families\nof Ravenna.  She to whom Dryden has given the name of Honoria, in\nthe fable so admirably paraphrased from Boccaccio, was of the\nformer: her lover and the specter were of the Anastagi family.\n\nv. 111.  The ladies, &c.]  These two lines express the true\nspirit of chivalry.  \"Agi\" is understood by the commentators whom\nI have consulted,to mean \"the ease procured for others by the\nexertions of knight-errantry.\"  But surely it signifies the\nalternation of ease with labour.\n\nv. 114.  O Brettinoro.]  A beautifully situated castle in\nRomagna, the hospitable residence of Guido del Duca, who is here\nspeaking.\n\nv. 118.  Baynacavallo.]  A castle between Imola and Ravenna\n\nv. 118.  Castracaro ill\nAnd Conio worse.]  Both in Romagna.\n\nv. 121.  Pagani.]  The Pagani were lords of Faenza and Imola. One\nof them Machinardo, was named the Demon, from his treachery.\nSee Hell, Canto XXVII. 47, and Note.\n\nv. 124.  Hugolin.]  Ugolino Ubaldini, a noble and virtuous person\nin Faenza, who, on account of his age probably, was not likely to\nleave any offspring behind him.  He is enumerated among the poets\nby Crescimbeni, and Tiraboschi.  Mr. Matthias\'s edit. vol. i. 143\n\nv. 136.  Whosoever finds Will slay me.] The words of Cain, Gen.\ne. iv. 14.\n\nv. 142.  Aglauros.]  Ovid, Met.  I, ii.  fate. 12.\n\nv. 145.  There was the galling bit.]  Referring to what had been\nbefore said, Canto XIII.  35.\n\nCANTO XV\n\nv. 1.  As much.]  It wanted three hours of sunset.\n\nv. 16.  As when the ray.]  Compare Virg. Aen. 1.viii. 22, and\nApol. Rhod. 1. iii. 755.\n\nv. 19.  Ascending at a glance.]  Lucretius, 1. iv. 215.\n\nv. 20.  Differs from the stone.]  The motion of light being\nquicker  than that of a stone through an equal space.\n\nv. 38.  Blessed the merciful.  Matt. c. v. 7.\n\nv. 43.  Romagna\'s spirit.] Guido del Duea, of Brettinoro whom we\nhave seen in the preceding Canto.\n\nv. 87.  A dame.]  Luke, c. ii.  18\n\nv. 101.  How shall we those requite.]  The answer of Pisistratus\nthe tyrant to his wife, when she urged him to inflict the\npun");

                struct disk_t* disk = disk_open_from_file("subtract_fat12_volume.img");
                test_error(disk != NULL, "Funkcja disk_open_from_file() niepoprawnie otworzyła plik");
                onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)

                struct volume_t* volume = fat_open(disk, 0);
                test_error(volume != NULL, "Funkcja fat_open() niepoprawnie otworzyła wolumin");
                onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)

                struct file_t* file = file_open(volume, "MULTIPLY.BIN");
                test_error(file != NULL, "Funkcja file_open() niepoprawnie otworzyła plik");
                onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)

                for (int i = 0; i < 3749; ++i)
                {
                    char c;
                    int res = file_read(&c, 1, 1, file);
                    test_error(res == 1, "Funkcja file_read() powinna zwrócić wartość 1, a zwróciła %d", res);
                    onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)
                    test_error(c == expected_filecontent[i], "Funkcja file_read() powinna odczytać w kroku %d znak %c, a odczytała znak %c", i, expected_filecontent[i], c);
                }

                char c;
                int res = file_read(&c, 1, 1, file);
                test_error(res == 0, "Funkcja file_read() powinna zwrócić wartość 0, a zwróciła %d", res);

                file_close(file);
                fat_close(volume);
                disk_close(disk);

                test_no_heap_leakage();
                onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)
            
    //
    // -----------
    //

    // przywrócenie podstawowych parametów przydzielania zasobów (jeśli to tylko możliwe)
    rldebug_reset_limits();
    test_file_write_limit_restore();
    
    test_ok();
}

//
//  Test 22: Sprawdzanie poprawności działania funkcji file_read
//
void UTEST22(void)
{
    // informacje o teście
    test_start(22, "Sprawdzanie poprawności działania funkcji file_read", __LINE__);

    // uwarunkowanie zasobów - pamięci, itd...
    test_file_write_limit_setup(33554432);
    rldebug_reset_limits();
    
    //
    // -----------
    //
    

                char expected_filecontent[3365] = "";

                strcat(expected_filecontent, "wond\'ring and suspense,\nReplied:  \"I see that thou believ\'st these things,\nBecause I tell them, but discern\'st not how;\nSo that thy knowledge waits not on thy faith:\nAs one who knows the name of thing by rote,\nBut is a stranger to its properties,\nTill other\'s tongue reveal them.  Fervent love\nAnd lively hope with violence assail\nThe kingdom of the heavens, and overcome\nThe will of the Most high; not in such sort\nAs man prevails o\'er man; but conquers it,\nBecause \'t is willing to be conquer\'d, still,\nThough conquer\'d, by its mercy conquering.\n     \"Those, in the eye who live the first and fifth,\nCause thee to marvel, in that thou behold\'st\nThe region of the angels deck\'d with them.\nThey quitted not their bodies, as thou deem\'st,\nGentiles but Christians, in firm rooted faith,\nThis of the feet in future to be pierc\'d,\nThat of feet nail\'d already to the cross.\nOne from the barrier of the dark abyss,\nWhere never any with good will returns,\nCame back unto his bones.  Of lively hope\nSuch was the meed; of lively hope, that wing\'d\nThe prayers sent up to God for his release,\nAnd put power into them to bend his will.\nThe glorious Spirit, of whom I speak to thee,\nA little while returning to the flesh,\nBeliev\'d in him, who had the means to help,\nAnd, in believing, nourish\'d such a flame\nOf holy love, that at the second death\nHe was made sharer in our gamesome mirth.\nThe other, through the riches of that grace,\nWhich from so deep a fountain doth distil,\nAs never eye created saw its rising,\nPlac\'d all his love below on just and right:\nWherefore of grace God op\'d in him the eye\nTo the redemption of mankind to come;\nWherein believing, he endur\'d no more\nThe filth of paganism, and for their ways\nRebuk\'d the stubborn nations.  The three nymphs,\nWhom at the right wheel thou beheldst advancing,\nWere sponsors for him more than thousand years\nBefore baptizing.  O how far remov\'d,\nPredestination!  is thy root from such\nAs see not the First cause entire: and ye,\nO mortal men!  be wary how ye judge:\nFor we, who see our Maker, know not yet\nThe number of the chosen: and esteem\nSuch scantiness of knowledge our delight:\nFor all our good is in that primal good\nConcentrate, and God\'s will and ours are one.\"\n     So, by that form divine, was giv\'n to me\nSweet medicine to clear and strengthen sight,\nAnd, as one handling skillfully the harp,\nAttendant on some skilful songster\'s voice\nBids the chords vibrate, and therein the song\nAcquires more pleasure; so, the whilst it spake,\nIt doth remember me, that I beheld\nThe pair of blessed luminaries move.\nLike the accordant twinkling of two eyes,\nTheir beamy circlets, dancing to the sounds.\n\n\n\nCANTO XXI\n\nAgain mine eyes were fix\'d on Beatrice,\nAnd with mine eyes my soul, that in her looks\nFound all contentment.  Yet no smile she wore\nAnd, \"Did I smile,\" quoth she, \"thou wouldst be straight\nLike Semele when into ashes turn\'d:\nFor, mounting these eternal palace-stairs,\nMy beauty, which the loftier it climbs,\nAs thou hast noted, still doth kindle more,\nSo shines, that, were no temp\'ring interpos\'d,\nThy mortal puissance would from its rays\nShrink, as the leaf doth from the thunderbolt.\nInto the seventh splendour are we wafted,\nThat underneath the burning lion\'s breast\nBeams, in this hour, commingled with his might,\nThy mind be with thine eyes: and in them mirror\'d\nThe shape, which in this mirror sha");

                struct disk_t* disk = disk_open_from_file("subtract_fat12_volume.img");
                test_error(disk != NULL, "Funkcja disk_open_from_file() niepoprawnie otworzyła plik");
                onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)

                struct volume_t* volume = fat_open(disk, 0);
                test_error(volume != NULL, "Funkcja fat_open() niepoprawnie otworzyła wolumin");
                onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)

                struct file_t* file = file_open(volume, "THOUSAND.TXT");
                test_error(file != NULL, "Funkcja file_open() niepoprawnie otworzyła plik");
                onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)

                for (int i = 0; i < 3364; ++i)
                {
                    char c;
                    int res = file_read(&c, 1, 1, file);
                    test_error(res == 1, "Funkcja file_read() powinna zwrócić wartość 1, a zwróciła %d", res);
                    onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)
                    test_error(c == expected_filecontent[i], "Funkcja file_read() powinna odczytać w kroku %d znak %c, a odczytała znak %c", i, expected_filecontent[i], c);
                }

                char c;
                int res = file_read(&c, 1, 1, file);
                test_error(res == 0, "Funkcja file_read() powinna zwrócić wartość 0, a zwróciła %d", res);

                file_close(file);
                fat_close(volume);
                disk_close(disk);

                test_no_heap_leakage();
                onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)
            
    //
    // -----------
    //

    // przywrócenie podstawowych parametów przydzielania zasobów (jeśli to tylko możliwe)
    rldebug_reset_limits();
    test_file_write_limit_restore();
    
    test_ok();
}

//
//  Test 23: Sprawdzanie poprawności działania funkcji file_read
//
void UTEST23(void)
{
    // informacje o teście
    test_start(23, "Sprawdzanie poprawności działania funkcji file_read", __LINE__);

    // uwarunkowanie zasobów - pamięci, itd...
    test_file_write_limit_setup(33554432);
    rldebug_reset_limits();
    
    //
    // -----------
    //
    

                char expected_filecontent[3028] = "";

                strcat(expected_filecontent, "onferred by that family on our poet at a subsequent perid of his\nexile in 1307.\n\n\n\nCanto XXV\n\nv.1.  The sinner ]  So Trissino\n        Poi facea con le man le fiche al cielo\n        Dicendo:  Togli, Iddio; che puoi piu farmi?\n               L\'ital. Lib. c. xii\n\nv. 12.  Thy seed]  Thy ancestry.\n\nv. 15.  Not him]  Capanaeus.  Canto XIV.\n\nv. 18.  On Marenna\'s marsh.]  An extensive tract near the\nsea-shore in Tuscany.\n\nv. 24.  Cacus.]  Virgil, Aen. l. viii. 193.\n\nv. 31.  A hundred blows.]  Less than ten blows, out of the\nhundred Hercules gave him, deprived him of feeling.\n\nv. 39.  Cianfa]  He is said to have been of the family of Donati\nat Florence.\n\nv. 57.  Thus up the shrinking paper.]\n        --All my bowels crumble up to dust.\n        I am a scribbled form, drawn up with a pen\n        Upon a parchment; and against this fire\n        Do I shrink up.\n               Shakespeare, K. John, a. v. s. 7.\n\nv. 61.  Agnello.]  Agnello Brunelleschi\n\nv. 77.  In that part.]  The navel.\n\nv. 81.  As if by sleep or fev\'rous fit assail\'d.]\n               O Rome!  thy head\n        Is drown\'d in sleep, and all thy body fev\'ry.\n               Ben Jonson\'s Catiline.\n\nv. 85.  Lucan.]  Phars. l. ix. 766 and 793.\n\nv. 87.  Ovid.] Metam. l. iv. and v.\n\nv. 121.  His sharpen\'d visage.]  Compare Milton, P. L. b. x. 511\n&c.\n\nv. 131.  Buoso.]  He is said to have been of the Donati family.\n\nv. 138.  Sciancato.]  Puccio Sciancato, a noted robber, whose\nfamilly, Venturi says, he has not been able to discover.\n\nv. 140.  Gaville.]  Francesco Guercio Cavalcante was killed at\nGaville, near Florence; and in revenge of his death several\ninhabitants of that district were put to death.\n\nCANTO XXVI\n\nv. 7. But if our minds.]\n\n        Namque sub Auroram, jam dormitante lucerna,\n        Somnia quo cerni tempore vera solent.\n               Ovid, Epist. xix\n\nThe same poetical superstition is alluded to in the Purgatory,\nCant. IX. and XXVII.\n\nv. 9. Shall feel what Prato.]  The poet prognosticates the\ncalamities which were soon to befal his native city, and which he\nsays, even her nearest neighbor, Prato, would wish her.  The\ncalamities more particularly pointed at, are said to be the fall\nof a wooden bridge over the Arno, in May, 1304, where a large\nmultitude were assembled to witness a representation  of hell nnd\nthe infernal torments, in consequence of which accident many\nlives were lost; and a conflagration that in the following month\ndestroyed more than seventeen hundred houses, many ofthem\nsumptuous buildings.  See G. Villani, Hist. l. viii. c. 70 and\n71.\n\nv. 22.  More than I am wont.]  \"When I reflect on the punishment\nallotted to those who do not give sincere and upright advice to\nothers I am more anxious than ever not to abuse to so bad a\npurpose those talents, whatever they may be, which Nature, or\nrather Providence, has conferred on me.\"  It is probable that\nthis declaration was the result of real feeling Textd have\ngiven great weight to\nany opinion or party he had espoused, and to whom indigence and\nexile might h");

                struct disk_t* disk = disk_open_from_file("subtract_fat12_volume.img");
                test_error(disk != NULL, "Funkcja disk_open_from_file() niepoprawnie otworzyła plik");
                onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)

                struct volume_t* volume = fat_open(disk, 0);
                test_error(volume != NULL, "Funkcja fat_open() niepoprawnie otworzyła wolumin");
                onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)

                struct file_t* file = file_open(volume, "LIFE");
                test_error(file != NULL, "Funkcja file_open() niepoprawnie otworzyła plik");
                onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)

                for (int i = 0; i < 3027; ++i)
                {
                    char c;
                    int res = file_read(&c, 1, 1, file);
                    test_error(res == 1, "Funkcja file_read() powinna zwrócić wartość 1, a zwróciła %d", res);
                    onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)
                    test_error(c == expected_filecontent[i], "Funkcja file_read() powinna odczytać w kroku %d znak %c, a odczytała znak %c", i, expected_filecontent[i], c);
                }

                char c;
                int res = file_read(&c, 1, 1, file);
                test_error(res == 0, "Funkcja file_read() powinna zwrócić wartość 0, a zwróciła %d", res);

                file_close(file);
                fat_close(volume);
                disk_close(disk);

                test_no_heap_leakage();
                onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)
            
    //
    // -----------
    //

    // przywrócenie podstawowych parametów przydzielania zasobów (jeśli to tylko możliwe)
    rldebug_reset_limits();
    test_file_write_limit_restore();
    
    test_ok();
}

//
//  Test 24: Sprawdzanie poprawności działania funkcji file_read
//
void UTEST24(void)
{
    // informacje o teście
    test_start(24, "Sprawdzanie poprawności działania funkcji file_read", __LINE__);

    // uwarunkowanie zasobów - pamięci, itd...
    test_file_write_limit_setup(33554432);
    rldebug_reset_limits();
    
    //
    // -----------
    //
    

                char expected_filecontent[3648] = "";

                strcat(expected_filecontent, "nd tears\nFollow so closely on the passion prompts them,\nThey wait not for the motions of the will\nIn natures most sincere.  I did but smile,\nAs one who winks; and thereupon the shade\nBroke off, and peer\'d into mine eyes, where best\nOur looks interpret. \"So to good event\nMayst thou conduct such great emprize,\" he cried,\n\"Say, why across thy visage beam\'d, but now,\nThe lightning of a smile!\"  On either part\nNow am I straiten\'d; one conjures me speak,\nTh\' other to silence binds me: whence a sigh\nI utter, and the sigh is heard.  \"Speak on; \"\nThe teacher cried;  \"and do not fear to speak,\nBut tell him what so earnestly he asks.\"\nWhereon I thus:  \"Perchance, O ancient spirit!\nThou marvel\'st at my smiling. There is room\nFor yet more wonder.  He who guides my ken\nOn high, he is that Mantuan, led by whom\nThou didst presume of men arid gods to sing.\nIf other cause thou deem\'dst for which I smil\'d,\nLeave it as not the true one; and believe\nThose words, thou spak\'st of him, indeed the cause.\"\n     Now down he bent t\' embrace my teacher\'s feet;\nBut he forbade him:  \"Brother!  do it not:\nThou art a shadow, and behold\'st a shade.\"\nHe rising answer\'d thus:  \"Now hast thou prov\'d\nThe force and ardour of the love I bear thee,\nWhen I forget we are but things of air,\nAnd as a substance treat an empty shade.\"\n\n\n\nCANTO XXII\n\nNow we had left the angel, who had turn\'d\nTo the sixth circle our ascending step,\nOne gash from off my forehead raz\'d: while they,\nWhose wishes tend to justice, shouted forth:\n\"Blessed!\"  and ended with, \"I thirst:\" and I,\nMore nimble than along the other straits,\nSo journey\'d, that, without the sense of toil,\nI follow\'d upward the swift-footed shades;\nWhen Virgil thus began:  \"Let its pure flame\nFrom virtue flow, and love can never fail\nTo warm another\'s bosom\' so the light\nShine manifestly forth.  Hence from that hour,\nWhen \'mongst us in the purlieus of the deep,\nCame down the spirit of Aquinum\'s hard,\nWho told of thine affection, my good will\nHath been for thee of quality as strong\nAs ever link\'d itself to one not seen.\nTherefore these stairs will now seem short to me.\nBut tell me: and if too secure I loose\nThe rein with a friend\'s license, as a friend\nForgive me, and speak now as with a friend:\nHow chanc\'d it covetous desire could find\nPlace in that bosom, \'midst such ample store\nOf wisdom, as thy zeal had treasur\'d there?\"\n     First somewhat mov\'d to laughter by his words,\nStatius replied: \"Each syllable of thine\nIs a dear pledge of love.  Things oft appear\nThat minister false matters to our doubts,\nWhen their true causes are remov\'d from sight.\nThy question doth assure me, thou believ\'st\nI was on earth a covetous man, perhaps\nBecause thou found\'st me in that circle plac\'d.\nKnow then I was too wide of avarice:\nAnd e\'en for that excess, thousands of moons\nHave wax\'d and wan\'d upon my sufferings.\nAnd were it not that I with heedful care\nNoted where thou exclaim\'st as if in ire\nWith human nature, \'Why, thou cursed thirst\nOf gold!  dost not with juster measure guide\nThe appetite of mortals?\'  I had met\nThe fierce encounter of the voluble rock.\nThen was I ware that with too ample wing\nThe hands may haste to lavishment, and turn\'d,\nAs from my other evil, so from this\nIn penitence.  How many from their grave\nShall with shorn locks arise, who living, aye\nAnd at life\'s last extreme, of this offence,\nThrough ignorance, did not repent.  And know,\nThe fault which lies direct from any sin\nIn level opposition, here With that\nWastes its green rankness on one common heap.\nTherefore if I have been with those, who wail\nTheir avarice, to cleanse me, through reverse\nOf their transgression, such ");

                struct disk_t* disk = disk_open_from_file("subtract_fat12_volume.img");
                test_error(disk != NULL, "Funkcja disk_open_from_file() niepoprawnie otworzyła plik");
                onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)

                struct volume_t* volume = fat_open(disk, 0);
                test_error(volume != NULL, "Funkcja fat_open() niepoprawnie otworzyła wolumin");
                onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)

                struct file_t* file = file_open(volume, "WHO.TX");
                test_error(file != NULL, "Funkcja file_open() niepoprawnie otworzyła plik");
                onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)

                for (int i = 0; i < 3647; ++i)
                {
                    char c;
                    int res = file_read(&c, 1, 1, file);
                    test_error(res == 1, "Funkcja file_read() powinna zwrócić wartość 1, a zwróciła %d", res);
                    onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)
                    test_error(c == expected_filecontent[i], "Funkcja file_read() powinna odczytać w kroku %d znak %c, a odczytała znak %c", i, expected_filecontent[i], c);
                }

                char c;
                int res = file_read(&c, 1, 1, file);
                test_error(res == 0, "Funkcja file_read() powinna zwrócić wartość 0, a zwróciła %d", res);

                file_close(file);
                fat_close(volume);
                disk_close(disk);

                test_no_heap_leakage();
                onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)
            
    //
    // -----------
    //

    // przywrócenie podstawowych parametów przydzielania zasobów (jeśli to tylko możliwe)
    rldebug_reset_limits();
    test_file_write_limit_restore();
    
    test_ok();
}

//
//  Test 25: Sprawdzanie poprawności działania funkcji file_read
//
void UTEST25(void)
{
    // informacje o teście
    test_start(25, "Sprawdzanie poprawności działania funkcji file_read", __LINE__);

    // uwarunkowanie zasobów - pamięci, itd...
    test_file_write_limit_setup(33554432);
    rldebug_reset_limits();
    
    //
    // -----------
    //
    

                char expected_filecontent[1537] = "";

                strcat(expected_filecontent, "       And silent as the moon, &c\nThe same metaphor will recur, Canto V. v. 29.\n        Into a place I came\n       Where light was silent all.\n\nv. 65.  When the power of Julius.] This is explained by the\ncommentators to mean \"Although it was rather late with respect to\nmy birth before Julius Caesar assumed the supreme authority, and\nmade himself perpetual dictator.\"\n\nv. 98.  That greyhound.]  This passage is intended as an eulogium\non the liberal spirit of his Veronese patron Can Grande della\nScala.\n\nv. 102.  \'Twizt either Feltro.]  Verona, the country of Can della\nScala, is situated between Feltro, a city in the Marca\nTrivigiana, and Monte Feltro, a city in the territory of Urbino.\n\nv. 103.  Italia\'s plains.]  \"Umile Italia,\" from Virgil, Aen lib.\niii. 522.\n        Humilemque videmus\n       Italiam.\n\nv. 115.  Content in fire.]  The spirits in Purgatory.\n\nv. 118.  A spirit worthier.]  Beatrice, who conducts the Poet\nthrough Paradise.\n\nv. 130.  Saint Peter\'s gate.]  The gate of Purgatory, which the\nPoet feigns to be guarded by an angel placed on that station by\nSt. Peter.\n\nCANTO II\n\nv. 1.  Now was the day.]  A compendium of Virgil\'s description\nAen. lib. iv 522.  Nox erat, &c. Compare Apollonius Rhodius, lib\niii. 744, and lib. iv. 1058\n\nv. 8.  O mind.]\n        O thought that write all that I met,\n        And in the tresorie it set\n        Of my braine, now shall men see\n        If any virtue in thee be.\n               Chaucer.  Temple of Fame, b. ii. v.18\n\nv. 14.  Silvius\'sire.] Aeneas.\n\nv. 30.  The chosen vesse");

                struct disk_t* disk = disk_open_from_file("subtract_fat12_volume.img");
                test_error(disk != NULL, "Funkcja disk_open_from_file() niepoprawnie otworzyła plik");
                onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)

                struct volume_t* volume = fat_open(disk, 0);
                test_error(volume != NULL, "Funkcja fat_open() niepoprawnie otworzyła wolumin");
                onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)

                struct file_t* file = file_open(volume, "AIR.BIN");
                test_error(file != NULL, "Funkcja file_open() niepoprawnie otworzyła plik");
                onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)

                for (int i = 0; i < 1536; ++i)
                {
                    char c;
                    int res = file_read(&c, 1, 1, file);
                    test_error(res == 1, "Funkcja file_read() powinna zwrócić wartość 1, a zwróciła %d", res);
                    onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)
                    test_error(c == expected_filecontent[i], "Funkcja file_read() powinna odczytać w kroku %d znak %c, a odczytała znak %c", i, expected_filecontent[i], c);
                }

                char c;
                int res = file_read(&c, 1, 1, file);
                test_error(res == 0, "Funkcja file_read() powinna zwrócić wartość 0, a zwróciła %d", res);

                file_close(file);
                fat_close(volume);
                disk_close(disk);

                test_no_heap_leakage();
                onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)
            
    //
    // -----------
    //

    // przywrócenie podstawowych parametów przydzielania zasobów (jeśli to tylko możliwe)
    rldebug_reset_limits();
    test_file_write_limit_restore();
    
    test_ok();
}

//
//  Test 26: Sprawdzanie poprawności działania funkcji file_read
//
void UTEST26(void)
{
    // informacje o teście
    test_start(26, "Sprawdzanie poprawności działania funkcji file_read", __LINE__);

    // uwarunkowanie zasobów - pamięci, itd...
    test_file_write_limit_setup(33554432);
    rldebug_reset_limits();
    
    //
    // -----------
    //
    

                char expected_filecontent[287] = "";

                strcat(expected_filecontent, "nto the tears,\nWith which I hasten that whereof thou spak\'st.\nI have on earth a kinswoman; her name\nAlagia, worthy in herself, so ill\nExample of our house corrupt her not:\nAnd she is all remaineth of me there.\"\n\n\n\nCANTO XX\n\nIll strives the will, \'gainst will more wise that strives\nHis ");

                struct disk_t* disk = disk_open_from_file("subtract_fat12_volume.img");
                test_error(disk != NULL, "Funkcja disk_open_from_file() niepoprawnie otworzyła plik");
                onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)

                struct volume_t* volume = fat_open(disk, 0);
                test_error(volume != NULL, "Funkcja fat_open() niepoprawnie otworzyła wolumin");
                onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)

                struct file_t* file = file_open(volume, "FORM.BIN");
                test_error(file != NULL, "Funkcja file_open() niepoprawnie otworzyła plik");
                onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)

                for (int i = 0; i < 286; ++i)
                {
                    char c;
                    int res = file_read(&c, 1, 1, file);
                    test_error(res == 1, "Funkcja file_read() powinna zwrócić wartość 1, a zwróciła %d", res);
                    onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)
                    test_error(c == expected_filecontent[i], "Funkcja file_read() powinna odczytać w kroku %d znak %c, a odczytała znak %c", i, expected_filecontent[i], c);
                }

                char c;
                int res = file_read(&c, 1, 1, file);
                test_error(res == 0, "Funkcja file_read() powinna zwrócić wartość 0, a zwróciła %d", res);

                file_close(file);
                fat_close(volume);
                disk_close(disk);

                test_no_heap_leakage();
                onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)
            
    //
    // -----------
    //

    // przywrócenie podstawowych parametów przydzielania zasobów (jeśli to tylko możliwe)
    rldebug_reset_limits();
    test_file_write_limit_restore();
    
    test_ok();
}

//
//  Test 27: Sprawdzanie poprawności działania funkcji file_read
//
void UTEST27(void)
{
    // informacje o teście
    test_start(27, "Sprawdzanie poprawności działania funkcji file_read", __LINE__);

    // uwarunkowanie zasobów - pamięci, itd...
    test_file_write_limit_setup(33554432);
    rldebug_reset_limits();
    
    //
    // -----------
    //
    
            char *filecontent = (char *)calloc(3421, 1);
            char expected_filecontent[3422] = "";

            strcat(expected_filecontent, "His wings are pointed, for there always throng\nAll such as not to Archeron descend.\"\n     Then I: \"If new laws have not quite destroy\'d\nMemory and use of that sweet song of love,\nThat while all my cares had power to \'swage;\nPlease thee with it a little to console\nMy spirit, that incumber\'d with its frame,\nTravelling so far, of pain is overcome.\"\n     \"Love that discourses in my thoughts.\"  He then\nBegan in such soft accents, that within\nThe sweetness thrills me yet.  My gentle guide\nAnd all who came with him, so well were pleas\'d,\nThat seem\'d naught else might in their thoughts have room.\n     Fast fix\'d in mute attention to his notes\nWe stood, when lo!  that old man venerable\nExclaiming, \"How is this, ye tardy spirits?\nWhat negligence detains you loit\'ring here?\nRun to the mountain to cast off those scales,\nThat from your eyes the sight of God conceal.\"\n     As a wild flock of pigeons, to their food\nCollected, blade or tares, without their pride\nAccustom\'d, and in still and quiet sort,\nIf aught alarm them, suddenly desert\nTheir meal, assail\'d by more important care;\nSo I that new-come troop beheld, the song\nDeserting, hasten to the mountain\'s side,\nAs one who goes yet where he tends knows not.\n     Nor with less hurried step did we depart.\n\n\n\nCANTO III\n\nThem sudden flight had scatter\'d over the plain,\nTurn\'d tow\'rds the mountain, whither reason\'s voice\nDrives us; I to my faithful company\nAdhering, left it not.  For how of him\nDepriv\'d, might I have sped, or who beside\nWould o\'er the mountainous tract have led my steps\nHe with the bitter pang of self-remorse\nSeem\'d smitten.  O clear conscience and upright\nHow doth a little fling wound thee sore!\n     Soon as his feet desisted (slack\'ning pace),\nFrom haste, that mars all decency of act,\nMy mind, that in itself before was wrapt,\nIts thoughts expanded, as with joy restor\'d:\nAnd full against the steep ascent I set\nMy face, where highest to heav\'n its top o\'erflows.\n     The sun, that flar\'d behind, with ruddy beam\nBefore my form was broken; for in me\nHis rays resistance met.  I turn\'d aside\nWith fear of being left, when I beheld\nOnly before myself the ground obscur\'d.\nWhen thus my solace, turning him around,\nBespake me kindly:  \"Why distrustest thou?\nBeliev\'st not I am with thee, thy sure guide?\nIt now is evening there, where buried lies\nThe body, in which I cast a shade, remov\'d\nTo Naples from Brundusium\'s wall.  Nor thou\nMarvel, if before me no shadow fall,\nMore than that in the sky element\nOne ray obstructs not other.  To endure\nTorments of heat and cold extreme, like frames\nThat virtue hath dispos\'d, which how it works\nWills not to us should be reveal\'d.  Insane\nWho hopes, our reason may that space explore,\nWhich holds three persons in one substance knit.\nSeek not the wherefore, race of human kind;\nCould ye have seen the whole, no need had been\nFor Mary to bring forth.  Moreover ye\nHave seen such men desiring fruitlessly;\nTo whose desires repose would have been giv\'n,\nThat now but serve them for eternal grief.\nI speak of Plato, and the Stagyrite,\nAnd others many more.\"  And then he bent\nDownwards his forehead, and in troubled mood\nBroke off his speech.  Meanwhile we had arriv\'d\nFar as the mountain\'s foot, and there the rock\nFound of so steep ascent, that nimblest steps\nTo climb it had been vain.  The most remote\nMost wild untrodden path, in all the tract\n\'Twixt Lerice and Turbia were to this\nA ladder easy\' an");

            struct disk_t* disk = disk_open_from_file("subtract_fat12_volume.img");
            test_error(disk != NULL, "Funkcja disk_open_from_file() niepoprawnie otworzyła plik");
            onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)

            struct volume_t* volume = fat_open(disk, 0);
            test_error(volume != NULL, "Funkcja fat_open() niepoprawnie otworzyła wolumin");
            onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)

            struct file_t* file = file_open(volume, "TAIL");
            test_error(file != NULL, "Funkcja file_open() niepoprawnie otworzyła plik");
            onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)

            int i;
            for (i = 0; i < 488; ++i)
            {
                int res = file_read(filecontent + 7 * i, 7, 1, file);
                test_error(res == 1, "Funkcja file_read() powinna zwrócić wartość 1, a zwróciła %d", res);
                onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)
            }

            int res = file_read(filecontent + 7 * i, 7, 1, file);
            test_error(res == 0, "Funkcja file_read() powinna zwrócić wartość 0, a zwróciła %d", res);
            onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)

            int diff_pos = mem_find_first_difference(filecontent, expected_filecontent, 3421);

            // jeśli jest, to raportuj błąd
            test_error(diff_pos == -1, "Dane wczytane z pliku nie są poprawne; różnica w bajcie %d; jest 0x%02x a powinno być 0x%02x",
                diff_pos, mem_get_byte(filecontent, diff_pos), mem_get_byte(expected_filecontent, diff_pos));

            onerror_compare_memory(expected_filecontent, filecontent, 3421);

            free(filecontent);
            file_close(file);
            fat_close(volume);
            disk_close(disk);

            test_no_heap_leakage();
            onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)
        
    //
    // -----------
    //

    // przywrócenie podstawowych parametów przydzielania zasobów (jeśli to tylko możliwe)
    rldebug_reset_limits();
    test_file_write_limit_restore();
    
    test_ok();
}

//
//  Test 28: Sprawdzanie poprawności działania funkcji file_read
//
void UTEST28(void)
{
    // informacje o teście
    test_start(28, "Sprawdzanie poprawności działania funkcji file_read", __LINE__);

    // uwarunkowanie zasobów - pamięci, itd...
    test_file_write_limit_setup(33554432);
    rldebug_reset_limits();
    
    //
    // -----------
    //
    

            char *filecontent0 = (char *)calloc(3421, 1);
    char *filecontent1 = (char *)calloc(3749, 1);
    char *filecontent2 = (char *)calloc(3364, 1);
    char *filecontent3 = (char *)calloc(3027, 1);
    char *filecontent4 = (char *)calloc(3647, 1);
    char *filecontent5 = (char *)calloc(1536, 1);
    char *filecontent6 = (char *)calloc(286, 1);

            char expected_filecontent0[3422] = "";
    char expected_filecontent1[3750] = "";
    char expected_filecontent2[3365] = "";
    char expected_filecontent3[3028] = "";
    char expected_filecontent4[3648] = "";
    char expected_filecontent5[1537] = "";
    char expected_filecontent6[287] = "";

            strcat(expected_filecontent0, "His wings are pointed, for there always throng\nAll such as not to Archeron descend.\"\n     Then I: \"If new laws have not quite destroy\'d\nMemory and use of that sweet song of love,\nThat while all my cares had power to \'swage;\nPlease thee with it a little to console\nMy spirit, that incumber\'d with its frame,\nTravelling so far, of pain is overcome.\"\n     \"Love that discourses in my thoughts.\"  He then\nBegan in such soft accents, that within\nThe sweetness thrills me yet.  My gentle guide\nAnd all who came with him, so well were pleas\'d,\nThat seem\'d naught else might in their thoughts have room.\n     Fast fix\'d in mute attention to his notes\nWe stood, when lo!  that old man venerable\nExclaiming, \"How is this, ye tardy spirits?\nWhat negligence detains you loit\'ring here?\nRun to the mountain to cast off those scales,\nThat from your eyes the sight of God conceal.\"\n     As a wild flock of pigeons, to their food\nCollected, blade or tares, without their pride\nAccustom\'d, and in still and quiet sort,\nIf aught alarm them, suddenly desert\nTheir meal, assail\'d by more important care;\nSo I that new-come troop beheld, the song\nDeserting, hasten to the mountain\'s side,\nAs one who goes yet where he tends knows not.\n     Nor with less hurried step did we depart.\n\n\n\nCANTO III\n\nThem sudden flight had scatter\'d over the plain,\nTurn\'d tow\'rds the mountain, whither reason\'s voice\nDrives us; I to my faithful company\nAdhering, left it not.  For how of him\nDepriv\'d, might I have sped, or who beside\nWould o\'er the mountainous tract have led my steps\nHe with the bitter pang of self-remorse\nSeem\'d smitten.  O clear conscience and upright\nHow doth a little fling wound thee sore!\n     Soon as his feet desisted (slack\'ning pace),\nFrom haste, that mars all decency of act,\nMy mind, that in itself before was wrapt,\nIts thoughts expanded, as with joy restor\'d:\nAnd full against the steep ascent I set\nMy face, where highest to heav\'n its top o\'erflows.\n     The sun, that flar\'d behind, with ruddy beam\nBefore my form was broken; for in me\nHis rays resistance met.  I turn\'d aside\nWith fear of being left, when I beheld\nOnly before myself the ground obscur\'d.\nWhen thus my solace, turning him around,\nBespake me kindly:  \"Why distrustest thou?\nBeliev\'st not I am with thee, thy sure guide?\nIt now is evening there, where buried lies\nThe body, in which I cast a shade, remov\'d\nTo Naples from Brundusium\'s wall.  Nor thou\nMarvel, if before me no shadow fall,\nMore than that in the sky element\nOne ray obstructs not other.  To endure\nTorments of heat and cold extreme, like frames\nThat virtue hath dispos\'d, which how it works\nWills not to us should be reveal\'d.  Insane\nWho hopes, our reason may that space explore,\nWhich holds three persons in one substance knit.\nSeek not the wherefore, race of human kind;\nCould ye have seen the whole, no need had been\nFor Mary to bring forth.  Moreover ye\nHave seen such men desiring fruitlessly;\nTo whose desires repose would have been giv\'n,\nThat now but serve them for eternal grief.\nI speak of Plato, and the Stagyrite,\nAnd others many more.\"  And then he bent\nDownwards his forehead, and in troubled mood\nBroke off his speech.  Meanwhile we had arriv\'d\nFar as the mountain\'s foot, and there the rock\nFound of so steep ascent, that nimblest steps\nTo climb it had been vain.  The most remote\nMost wild untrodden path, in all the tract\n\'Twixt Lerice and Turbia were to this\nA ladder easy\' an");strcat(expected_filecontent1, "seaport on the\nconfines of the Maremma, has led them to conceive hopes of\nbecoming a naval power: but this scheme will prove as chimerical\nas their former plan for the discovery of a subterraneous stream\nunder their city.\"  Why they gave the appellation of Diana to the\nimagined stream, Venturi says he leaves it to the antiquaries of\nSienna to conjecture.\n\nCANTO XIV\n\nv. 34.  Maim\'d of Pelorus.]  Virg. Aen. 1. iii. 414.\n\n--a hill\nTorn from Pelorus\nMilton P. L. b. i. 232\n\nv. 45.  \'Midst brute swine.]  The people of Casentino.\n\nv. 49.  Curs.]  The Arno leaves Arezzo about four miles to the\nleft.\n\nv. 53.  Wolves.]  The Florentines.\n\nv. 55.  Foxes.]  The Pisans\n\nv. 61.  Thy grandson.]  Fulcieri de\' Calboli, grandson of\nRinieri de\' Calboli, who is here spoken to.  The atrocities\npredicted came to pass in 1302.  See G. Villani, 1.  viii c. 59\n\nv. 95.  \'Twixt Po, the mount, the Reno, and the shore.]  The\nboundaries of Romagna.\n\nv. 99.  Lizio.]  Lizio da Valbona, introduced into Boccaccio\'s\nDecameron, G. v. N, 4.\n\nv. 100.  Manardi, Traversaro, and Carpigna.1 Arrigo Manardi of\nFaenza, or as some say, of Brettinoro, Pier Traversaro, lord of\nRavenna, and Guido di Carpigna of Montefeltro.\n\nv. 102.  In Bologna the low artisan.]  One who had been a\nmechanic named Lambertaccio, arrived at almost supreme power in\nBologna.\n\nv. 103.  Yon Bernardin.]  Bernardin di Fosco, a man of low\norigin but great talents, who governed at Faenza.\n\nv. 107.  Prata.]  A place between Faenza and Ravenna\n\nv. 107.  Of Azzo him.] Ugolino of the Ubaldini family in Tuscany\nHe is recounted among the poets by Crescimbeni and Tiraboschi.\n\nv. 108.  Tignoso.] Federigo Tignoso of Rimini.\n\nv. 109.  Traversaro\'s house and Anastagio\'s.]  Two noble families\nof Ravenna.  She to whom Dryden has given the name of Honoria, in\nthe fable so admirably paraphrased from Boccaccio, was of the\nformer: her lover and the specter were of the Anastagi family.\n\nv. 111.  The ladies, &c.]  These two lines express the true\nspirit of chivalry.  \"Agi\" is understood by the commentators whom\nI have consulted,to mean \"the ease procured for others by the\nexertions of knight-errantry.\"  But surely it signifies the\nalternation of ease with labour.\n\nv. 114.  O Brettinoro.]  A beautifully situated castle in\nRomagna, the hospitable residence of Guido del Duca, who is here\nspeaking.\n\nv. 118.  Baynacavallo.]  A castle between Imola and Ravenna\n\nv. 118.  Castracaro ill\nAnd Conio worse.]  Both in Romagna.\n\nv. 121.  Pagani.]  The Pagani were lords of Faenza and Imola. One\nof them Machinardo, was named the Demon, from his treachery.\nSee Hell, Canto XXVII. 47, and Note.\n\nv. 124.  Hugolin.]  Ugolino Ubaldini, a noble and virtuous person\nin Faenza, who, on account of his age probably, was not likely to\nleave any offspring behind him.  He is enumerated among the poets\nby Crescimbeni, and Tiraboschi.  Mr. Matthias\'s edit. vol. i. 143\n\nv. 136.  Whosoever finds Will slay me.] The words of Cain, Gen.\ne. iv. 14.\n\nv. 142.  Aglauros.]  Ovid, Met.  I, ii.  fate. 12.\n\nv. 145.  There was the galling bit.]  Referring to what had been\nbefore said, Canto XIII.  35.\n\nCANTO XV\n\nv. 1.  As much.]  It wanted three hours of sunset.\n\nv. 16.  As when the ray.]  Compare Virg. Aen. 1.viii. 22, and\nApol. Rhod. 1. iii. 755.\n\nv. 19.  Ascending at a glance.]  Lucretius, 1. iv. 215.\n\nv. 20.  Differs from the stone.]  The motion of light being\nquicker  than that of a stone through an equal space.\n\nv. 38.  Blessed the merciful.  Matt. c. v. 7.\n\nv. 43.  Romagna\'s spirit.] Guido del Duea, of Brettinoro whom we\nhave seen in the preceding Canto.\n\nv. 87.  A dame.]  Luke, c. ii.  18\n\nv. 101.  How shall we those requite.]  The answer of Pisistratus\nthe tyrant to his wife, when she urged him to inflict the\npun");strcat(expected_filecontent2, "wond\'ring and suspense,\nReplied:  \"I see that thou believ\'st these things,\nBecause I tell them, but discern\'st not how;\nSo that thy knowledge waits not on thy faith:\nAs one who knows the name of thing by rote,\nBut is a stranger to its properties,\nTill other\'s tongue reveal them.  Fervent love\nAnd lively hope with violence assail\nThe kingdom of the heavens, and overcome\nThe will of the Most high; not in such sort\nAs man prevails o\'er man; but conquers it,\nBecause \'t is willing to be conquer\'d, still,\nThough conquer\'d, by its mercy conquering.\n     \"Those, in the eye who live the first and fifth,\nCause thee to marvel, in that thou behold\'st\nThe region of the angels deck\'d with them.\nThey quitted not their bodies, as thou deem\'st,\nGentiles but Christians, in firm rooted faith,\nThis of the feet in future to be pierc\'d,\nThat of feet nail\'d already to the cross.\nOne from the barrier of the dark abyss,\nWhere never any with good will returns,\nCame back unto his bones.  Of lively hope\nSuch was the meed; of lively hope, that wing\'d\nThe prayers sent up to God for his release,\nAnd put power into them to bend his will.\nThe glorious Spirit, of whom I speak to thee,\nA little while returning to the flesh,\nBeliev\'d in him, who had the means to help,\nAnd, in believing, nourish\'d such a flame\nOf holy love, that at the second death\nHe was made sharer in our gamesome mirth.\nThe other, through the riches of that grace,\nWhich from so deep a fountain doth distil,\nAs never eye created saw its rising,\nPlac\'d all his love below on just and right:\nWherefore of grace God op\'d in him the eye\nTo the redemption of mankind to come;\nWherein believing, he endur\'d no more\nThe filth of paganism, and for their ways\nRebuk\'d the stubborn nations.  The three nymphs,\nWhom at the right wheel thou beheldst advancing,\nWere sponsors for him more than thousand years\nBefore baptizing.  O how far remov\'d,\nPredestination!  is thy root from such\nAs see not the First cause entire: and ye,\nO mortal men!  be wary how ye judge:\nFor we, who see our Maker, know not yet\nThe number of the chosen: and esteem\nSuch scantiness of knowledge our delight:\nFor all our good is in that primal good\nConcentrate, and God\'s will and ours are one.\"\n     So, by that form divine, was giv\'n to me\nSweet medicine to clear and strengthen sight,\nAnd, as one handling skillfully the harp,\nAttendant on some skilful songster\'s voice\nBids the chords vibrate, and therein the song\nAcquires more pleasure; so, the whilst it spake,\nIt doth remember me, that I beheld\nThe pair of blessed luminaries move.\nLike the accordant twinkling of two eyes,\nTheir beamy circlets, dancing to the sounds.\n\n\n\nCANTO XXI\n\nAgain mine eyes were fix\'d on Beatrice,\nAnd with mine eyes my soul, that in her looks\nFound all contentment.  Yet no smile she wore\nAnd, \"Did I smile,\" quoth she, \"thou wouldst be straight\nLike Semele when into ashes turn\'d:\nFor, mounting these eternal palace-stairs,\nMy beauty, which the loftier it climbs,\nAs thou hast noted, still doth kindle more,\nSo shines, that, were no temp\'ring interpos\'d,\nThy mortal puissance would from its rays\nShrink, as the leaf doth from the thunderbolt.\nInto the seventh splendour are we wafted,\nThat underneath the burning lion\'s breast\nBeams, in this hour, commingled with his might,\nThy mind be with thine eyes: and in them mirror\'d\nThe shape, which in this mirror sha");strcat(expected_filecontent3, "onferred by that family on our poet at a subsequent perid of his\nexile in 1307.\n\n\n\nCanto XXV\n\nv.1.  The sinner ]  So Trissino\n        Poi facea con le man le fiche al cielo\n        Dicendo:  Togli, Iddio; che puoi piu farmi?\n               L\'ital. Lib. c. xii\n\nv. 12.  Thy seed]  Thy ancestry.\n\nv. 15.  Not him]  Capanaeus.  Canto XIV.\n\nv. 18.  On Marenna\'s marsh.]  An extensive tract near the\nsea-shore in Tuscany.\n\nv. 24.  Cacus.]  Virgil, Aen. l. viii. 193.\n\nv. 31.  A hundred blows.]  Less than ten blows, out of the\nhundred Hercules gave him, deprived him of feeling.\n\nv. 39.  Cianfa]  He is said to have been of the family of Donati\nat Florence.\n\nv. 57.  Thus up the shrinking paper.]\n        --All my bowels crumble up to dust.\n        I am a scribbled form, drawn up with a pen\n        Upon a parchment; and against this fire\n        Do I shrink up.\n               Shakespeare, K. John, a. v. s. 7.\n\nv. 61.  Agnello.]  Agnello Brunelleschi\n\nv. 77.  In that part.]  The navel.\n\nv. 81.  As if by sleep or fev\'rous fit assail\'d.]\n               O Rome!  thy head\n        Is drown\'d in sleep, and all thy body fev\'ry.\n               Ben Jonson\'s Catiline.\n\nv. 85.  Lucan.]  Phars. l. ix. 766 and 793.\n\nv. 87.  Ovid.] Metam. l. iv. and v.\n\nv. 121.  His sharpen\'d visage.]  Compare Milton, P. L. b. x. 511\n&c.\n\nv. 131.  Buoso.]  He is said to have been of the Donati family.\n\nv. 138.  Sciancato.]  Puccio Sciancato, a noted robber, whose\nfamilly, Venturi says, he has not been able to discover.\n\nv. 140.  Gaville.]  Francesco Guercio Cavalcante was killed at\nGaville, near Florence; and in revenge of his death several\ninhabitants of that district were put to death.\n\nCANTO XXVI\n\nv. 7. But if our minds.]\n\n        Namque sub Auroram, jam dormitante lucerna,\n        Somnia quo cerni tempore vera solent.\n               Ovid, Epist. xix\n\nThe same poetical superstition is alluded to in the Purgatory,\nCant. IX. and XXVII.\n\nv. 9. Shall feel what Prato.]  The poet prognosticates the\ncalamities which were soon to befal his native city, and which he\nsays, even her nearest neighbor, Prato, would wish her.  The\ncalamities more particularly pointed at, are said to be the fall\nof a wooden bridge over the Arno, in May, 1304, where a large\nmultitude were assembled to witness a representation  of hell nnd\nthe infernal torments, in consequence of which accident many\nlives were lost; and a conflagration that in the following month\ndestroyed more than seventeen hundred houses, many ofthem\nsumptuous buildings.  See G. Villani, Hist. l. viii. c. 70 and\n71.\n\nv. 22.  More than I am wont.]  \"When I reflect on the punishment\nallotted to those who do not give sincere and upright advice to\nothers I am more anxious than ever not to abuse to so bad a\npurpose those talents, whatever they may be, which Nature, or\nrather Providence, has conferred on me.\"  It is probable that\nthis declaration was the result of real feeling Textd have\ngiven great weight to\nany opinion or party he had espoused, and to whom indigence and\nexile might h");strcat(expected_filecontent4, "nd tears\nFollow so closely on the passion prompts them,\nThey wait not for the motions of the will\nIn natures most sincere.  I did but smile,\nAs one who winks; and thereupon the shade\nBroke off, and peer\'d into mine eyes, where best\nOur looks interpret. \"So to good event\nMayst thou conduct such great emprize,\" he cried,\n\"Say, why across thy visage beam\'d, but now,\nThe lightning of a smile!\"  On either part\nNow am I straiten\'d; one conjures me speak,\nTh\' other to silence binds me: whence a sigh\nI utter, and the sigh is heard.  \"Speak on; \"\nThe teacher cried;  \"and do not fear to speak,\nBut tell him what so earnestly he asks.\"\nWhereon I thus:  \"Perchance, O ancient spirit!\nThou marvel\'st at my smiling. There is room\nFor yet more wonder.  He who guides my ken\nOn high, he is that Mantuan, led by whom\nThou didst presume of men arid gods to sing.\nIf other cause thou deem\'dst for which I smil\'d,\nLeave it as not the true one; and believe\nThose words, thou spak\'st of him, indeed the cause.\"\n     Now down he bent t\' embrace my teacher\'s feet;\nBut he forbade him:  \"Brother!  do it not:\nThou art a shadow, and behold\'st a shade.\"\nHe rising answer\'d thus:  \"Now hast thou prov\'d\nThe force and ardour of the love I bear thee,\nWhen I forget we are but things of air,\nAnd as a substance treat an empty shade.\"\n\n\n\nCANTO XXII\n\nNow we had left the angel, who had turn\'d\nTo the sixth circle our ascending step,\nOne gash from off my forehead raz\'d: while they,\nWhose wishes tend to justice, shouted forth:\n\"Blessed!\"  and ended with, \"I thirst:\" and I,\nMore nimble than along the other straits,\nSo journey\'d, that, without the sense of toil,\nI follow\'d upward the swift-footed shades;\nWhen Virgil thus began:  \"Let its pure flame\nFrom virtue flow, and love can never fail\nTo warm another\'s bosom\' so the light\nShine manifestly forth.  Hence from that hour,\nWhen \'mongst us in the purlieus of the deep,\nCame down the spirit of Aquinum\'s hard,\nWho told of thine affection, my good will\nHath been for thee of quality as strong\nAs ever link\'d itself to one not seen.\nTherefore these stairs will now seem short to me.\nBut tell me: and if too secure I loose\nThe rein with a friend\'s license, as a friend\nForgive me, and speak now as with a friend:\nHow chanc\'d it covetous desire could find\nPlace in that bosom, \'midst such ample store\nOf wisdom, as thy zeal had treasur\'d there?\"\n     First somewhat mov\'d to laughter by his words,\nStatius replied: \"Each syllable of thine\nIs a dear pledge of love.  Things oft appear\nThat minister false matters to our doubts,\nWhen their true causes are remov\'d from sight.\nThy question doth assure me, thou believ\'st\nI was on earth a covetous man, perhaps\nBecause thou found\'st me in that circle plac\'d.\nKnow then I was too wide of avarice:\nAnd e\'en for that excess, thousands of moons\nHave wax\'d and wan\'d upon my sufferings.\nAnd were it not that I with heedful care\nNoted where thou exclaim\'st as if in ire\nWith human nature, \'Why, thou cursed thirst\nOf gold!  dost not with juster measure guide\nThe appetite of mortals?\'  I had met\nThe fierce encounter of the voluble rock.\nThen was I ware that with too ample wing\nThe hands may haste to lavishment, and turn\'d,\nAs from my other evil, so from this\nIn penitence.  How many from their grave\nShall with shorn locks arise, who living, aye\nAnd at life\'s last extreme, of this offence,\nThrough ignorance, did not repent.  And know,\nThe fault which lies direct from any sin\nIn level opposition, here With that\nWastes its green rankness on one common heap.\nTherefore if I have been with those, who wail\nTheir avarice, to cleanse me, through reverse\nOf their transgression, such ");strcat(expected_filecontent5, "       And silent as the moon, &c\nThe same metaphor will recur, Canto V. v. 29.\n        Into a place I came\n       Where light was silent all.\n\nv. 65.  When the power of Julius.] This is explained by the\ncommentators to mean \"Although it was rather late with respect to\nmy birth before Julius Caesar assumed the supreme authority, and\nmade himself perpetual dictator.\"\n\nv. 98.  That greyhound.]  This passage is intended as an eulogium\non the liberal spirit of his Veronese patron Can Grande della\nScala.\n\nv. 102.  \'Twizt either Feltro.]  Verona, the country of Can della\nScala, is situated between Feltro, a city in the Marca\nTrivigiana, and Monte Feltro, a city in the territory of Urbino.\n\nv. 103.  Italia\'s plains.]  \"Umile Italia,\" from Virgil, Aen lib.\niii. 522.\n        Humilemque videmus\n       Italiam.\n\nv. 115.  Content in fire.]  The spirits in Purgatory.\n\nv. 118.  A spirit worthier.]  Beatrice, who conducts the Poet\nthrough Paradise.\n\nv. 130.  Saint Peter\'s gate.]  The gate of Purgatory, which the\nPoet feigns to be guarded by an angel placed on that station by\nSt. Peter.\n\nCANTO II\n\nv. 1.  Now was the day.]  A compendium of Virgil\'s description\nAen. lib. iv 522.  Nox erat, &c. Compare Apollonius Rhodius, lib\niii. 744, and lib. iv. 1058\n\nv. 8.  O mind.]\n        O thought that write all that I met,\n        And in the tresorie it set\n        Of my braine, now shall men see\n        If any virtue in thee be.\n               Chaucer.  Temple of Fame, b. ii. v.18\n\nv. 14.  Silvius\'sire.] Aeneas.\n\nv. 30.  The chosen vesse");strcat(expected_filecontent6, "nto the tears,\nWith which I hasten that whereof thou spak\'st.\nI have on earth a kinswoman; her name\nAlagia, worthy in herself, so ill\nExample of our house corrupt her not:\nAnd she is all remaineth of me there.\"\n\n\n\nCANTO XX\n\nIll strives the will, \'gainst will more wise that strives\nHis ");


            struct disk_t* disk = disk_open_from_file("subtract_fat12_volume.img");
            test_error(disk != NULL, "Funkcja disk_open_from_file() niepoprawnie otworzyła plik");
            onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)

            struct volume_t* volume = fat_open(disk, 0);
            test_error(volume != NULL, "Funkcja fat_open() niepoprawnie otworzyła wolumin");
            onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)

            
                    struct file_t* file0 = file_open(volume, "TAIL");
                    test_error(file0 != NULL, "Funkcja file_open() niepoprawnie otworzyła plik");
                    onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)"

            
                    struct file_t* file1 = file_open(volume, "MULTIPLY.BIN");
                    test_error(file1 != NULL, "Funkcja file_open() niepoprawnie otworzyła plik");
                    onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)"

            
                    struct file_t* file2 = file_open(volume, "THOUSAND.TXT");
                    test_error(file2 != NULL, "Funkcja file_open() niepoprawnie otworzyła plik");
                    onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)"

            
                    struct file_t* file3 = file_open(volume, "LIFE");
                    test_error(file3 != NULL, "Funkcja file_open() niepoprawnie otworzyła plik");
                    onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)"

            
                    struct file_t* file4 = file_open(volume, "WHO.TX");
                    test_error(file4 != NULL, "Funkcja file_open() niepoprawnie otworzyła plik");
                    onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)"

            
                    struct file_t* file5 = file_open(volume, "AIR.BIN");
                    test_error(file5 != NULL, "Funkcja file_open() niepoprawnie otworzyła plik");
                    onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)"

            
                    struct file_t* file6 = file_open(volume, "FORM.BIN");
                    test_error(file6 != NULL, "Funkcja file_open() niepoprawnie otworzyła plik");
                    onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)"

            
            
                size_t size0 = file_read(filecontent0, 1, 3421, file0);
                test_error(size0 == 3421, "Funkcja file_read() niepoprawnie wczytała dane z pliku, powinna wczytać 3421 bajtów, a wczytała %lu", size0);
                onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)
                int diff_pos0 = mem_find_first_difference(filecontent0, expected_filecontent0, 3421);
        
                // jeśli jest, to raportuj błąd
                test_error(diff_pos0 == -1, "Dane wczytane z pliku nie są poprawne; różnica w bajcie %d; jest 0x%02x a powinno być 0x%02x",
                    diff_pos0, mem_get_byte(filecontent0, diff_pos0), mem_get_byte(expected_filecontent0, diff_pos0));
        
                onerror_compare_memory(expected_filecontent0, filecontent0, 3421);
            
                size_t size1 = file_read(filecontent1, 1, 3749, file1);
                test_error(size1 == 3749, "Funkcja file_read() niepoprawnie wczytała dane z pliku, powinna wczytać 3749 bajtów, a wczytała %lu", size1);
                onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)
                int diff_pos1 = mem_find_first_difference(filecontent1, expected_filecontent1, 3749);
        
                // jeśli jest, to raportuj błąd
                test_error(diff_pos1 == -1, "Dane wczytane z pliku nie są poprawne; różnica w bajcie %d; jest 0x%02x a powinno być 0x%02x",
                    diff_pos1, mem_get_byte(filecontent1, diff_pos1), mem_get_byte(expected_filecontent1, diff_pos1));
        
                onerror_compare_memory(expected_filecontent1, filecontent1, 3749);
            
                size_t size2 = file_read(filecontent2, 1, 3364, file2);
                test_error(size2 == 3364, "Funkcja file_read() niepoprawnie wczytała dane z pliku, powinna wczytać 3364 bajtów, a wczytała %lu", size2);
                onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)
                int diff_pos2 = mem_find_first_difference(filecontent2, expected_filecontent2, 3364);
        
                // jeśli jest, to raportuj błąd
                test_error(diff_pos2 == -1, "Dane wczytane z pliku nie są poprawne; różnica w bajcie %d; jest 0x%02x a powinno być 0x%02x",
                    diff_pos2, mem_get_byte(filecontent2, diff_pos2), mem_get_byte(expected_filecontent2, diff_pos2));
        
                onerror_compare_memory(expected_filecontent2, filecontent2, 3364);
            
                size_t size3 = file_read(filecontent3, 1, 3027, file3);
                test_error(size3 == 3027, "Funkcja file_read() niepoprawnie wczytała dane z pliku, powinna wczytać 3027 bajtów, a wczytała %lu", size3);
                onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)
                int diff_pos3 = mem_find_first_difference(filecontent3, expected_filecontent3, 3027);
        
                // jeśli jest, to raportuj błąd
                test_error(diff_pos3 == -1, "Dane wczytane z pliku nie są poprawne; różnica w bajcie %d; jest 0x%02x a powinno być 0x%02x",
                    diff_pos3, mem_get_byte(filecontent3, diff_pos3), mem_get_byte(expected_filecontent3, diff_pos3));
        
                onerror_compare_memory(expected_filecontent3, filecontent3, 3027);
            
                size_t size4 = file_read(filecontent4, 1, 3647, file4);
                test_error(size4 == 3647, "Funkcja file_read() niepoprawnie wczytała dane z pliku, powinna wczytać 3647 bajtów, a wczytała %lu", size4);
                onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)
                int diff_pos4 = mem_find_first_difference(filecontent4, expected_filecontent4, 3647);
        
                // jeśli jest, to raportuj błąd
                test_error(diff_pos4 == -1, "Dane wczytane z pliku nie są poprawne; różnica w bajcie %d; jest 0x%02x a powinno być 0x%02x",
                    diff_pos4, mem_get_byte(filecontent4, diff_pos4), mem_get_byte(expected_filecontent4, diff_pos4));
        
                onerror_compare_memory(expected_filecontent4, filecontent4, 3647);
            
                size_t size5 = file_read(filecontent5, 1, 1536, file5);
                test_error(size5 == 1536, "Funkcja file_read() niepoprawnie wczytała dane z pliku, powinna wczytać 1536 bajtów, a wczytała %lu", size5);
                onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)
                int diff_pos5 = mem_find_first_difference(filecontent5, expected_filecontent5, 1536);
        
                // jeśli jest, to raportuj błąd
                test_error(diff_pos5 == -1, "Dane wczytane z pliku nie są poprawne; różnica w bajcie %d; jest 0x%02x a powinno być 0x%02x",
                    diff_pos5, mem_get_byte(filecontent5, diff_pos5), mem_get_byte(expected_filecontent5, diff_pos5));
        
                onerror_compare_memory(expected_filecontent5, filecontent5, 1536);
            
                size_t size6 = file_read(filecontent6, 1, 286, file6);
                test_error(size6 == 286, "Funkcja file_read() niepoprawnie wczytała dane z pliku, powinna wczytać 286 bajtów, a wczytała %lu", size6);
                onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)
                int diff_pos6 = mem_find_first_difference(filecontent6, expected_filecontent6, 286);
        
                // jeśli jest, to raportuj błąd
                test_error(diff_pos6 == -1, "Dane wczytane z pliku nie są poprawne; różnica w bajcie %d; jest 0x%02x a powinno być 0x%02x",
                    diff_pos6, mem_get_byte(filecontent6, diff_pos6), mem_get_byte(expected_filecontent6, diff_pos6));
        
                onerror_compare_memory(expected_filecontent6, filecontent6, 286);
            

            free(filecontent0);
    free(filecontent1);
    free(filecontent2);
    free(filecontent3);
    free(filecontent4);
    free(filecontent5);
    free(filecontent6);

            file_close(file0);
    file_close(file1);
    file_close(file2);
    file_close(file3);
    file_close(file4);
    file_close(file5);
    file_close(file6);


            fat_close(volume);
            disk_close(disk);

            test_no_heap_leakage();
            onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)
        
    //
    // -----------
    //

    // przywrócenie podstawowych parametów przydzielania zasobów (jeśli to tylko możliwe)
    rldebug_reset_limits();
    test_file_write_limit_restore();
    
    test_ok();
}

//
//  Test 29: Sprawdzanie poprawności działania funkcji file_seek
//
void UTEST29(void)
{
    // informacje o teście
    test_start(29, "Sprawdzanie poprawności działania funkcji file_seek", __LINE__);

    // uwarunkowanie zasobów - pamięci, itd...
    test_file_write_limit_setup(33554432);
    rldebug_reset_limits();
    
    //
    // -----------
    //
    
            char *filecontent = (char *)calloc(3027, 1);
            char expected_filecontent[3028] = "";

            strcat(expected_filecontent, "onferred by that family on our poet at a subsequent perid of his\nexile in 1307.\n\n\n\nCanto XXV\n\nv.1.  The sinner ]  So Trissino\n        Poi facea con le man le fiche al cielo\n        Dicendo:  Togli, Iddio; che puoi piu farmi?\n               L\'ital. Lib. c. xii\n\nv. 12.  Thy seed]  Thy ancestry.\n\nv. 15.  Not him]  Capanaeus.  Canto XIV.\n\nv. 18.  On Marenna\'s marsh.]  An extensive tract near the\nsea-shore in Tuscany.\n\nv. 24.  Cacus.]  Virgil, Aen. l. viii. 193.\n\nv. 31.  A hundred blows.]  Less than ten blows, out of the\nhundred Hercules gave him, deprived him of feeling.\n\nv. 39.  Cianfa]  He is said to have been of the family of Donati\nat Florence.\n\nv. 57.  Thus up the shrinking paper.]\n        --All my bowels crumble up to dust.\n        I am a scribbled form, drawn up with a pen\n        Upon a parchment; and against this fire\n        Do I shrink up.\n               Shakespeare, K. John, a. v. s. 7.\n\nv. 61.  Agnello.]  Agnello Brunelleschi\n\nv. 77.  In that part.]  The navel.\n\nv. 81.  As if by sleep or fev\'rous fit assail\'d.]\n               O Rome!  thy head\n        Is drown\'d in sleep, and all thy body fev\'ry.\n               Ben Jonson\'s Catiline.\n\nv. 85.  Lucan.]  Phars. l. ix. 766 and 793.\n\nv. 87.  Ovid.] Metam. l. iv. and v.\n\nv. 121.  His sharpen\'d visage.]  Compare Milton, P. L. b. x. 511\n&c.\n\nv. 131.  Buoso.]  He is said to have been of the Donati family.\n\nv. 138.  Sciancato.]  Puccio Sciancato, a noted robber, whose\nfamilly, Venturi says, he has not been able to discover.\n\nv. 140.  Gaville.]  Francesco Guercio Cavalcante was killed at\nGaville, near Florence; and in revenge of his death several\ninhabitants of that district were put to death.\n\nCANTO XXVI\n\nv. 7. But if our minds.]\n\n        Namque sub Auroram, jam dormitante lucerna,\n        Somnia quo cerni tempore vera solent.\n               Ovid, Epist. xix\n\nThe same poetical superstition is alluded to in the Purgatory,\nCant. IX. and XXVII.\n\nv. 9. Shall feel what Prato.]  The poet prognosticates the\ncalamities which were soon to befal his native city, and which he\nsays, even her nearest neighbor, Prato, would wish her.  The\ncalamities more particularly pointed at, are said to be the fall\nof a wooden bridge over the Arno, in May, 1304, where a large\nmultitude were assembled to witness a representation  of hell nnd\nthe infernal torments, in consequence of which accident many\nlives were lost; and a conflagration that in the following month\ndestroyed more than seventeen hundred houses, many ofthem\nsumptuous buildings.  See G. Villani, Hist. l. viii. c. 70 and\n71.\n\nv. 22.  More than I am wont.]  \"When I reflect on the punishment\nallotted to those who do not give sincere and upright advice to\nothers I am more anxious than ever not to abuse to so bad a\npurpose those talents, whatever they may be, which Nature, or\nrather Providence, has conferred on me.\"  It is probable that\nthis declaration was the result of real feeling Textd have\ngiven great weight to\nany opinion or party he had espoused, and to whom indigence and\nexile might h");

            struct disk_t* disk = disk_open_from_file("subtract_fat12_volume.img");
            test_error(disk != NULL, "Funkcja disk_open_from_file() niepoprawnie otworzyła plik");
            onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)

            struct volume_t* volume = fat_open(disk, 0);
            test_error(volume != NULL, "Funkcja fat_open() niepoprawnie otworzyła wolumin");
            onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)

            struct file_t* file = file_open(volume, "LIFE");
            test_error(file != NULL, "Funkcja file_open() niepoprawnie otworzyła plik");
            onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)

            file_seek(file, 1217, SEEK_SET);
        
            char c;
            int res = file_read(&c, 1, 1, file);
            test_error(res == 1, "Funkcja file_read() powinna zwrócić wartość 1, a zwróciła %d", res);
            onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)
            test_error(expected_filecontent[1217] == c, "Funkcja file_read() powinna odczyatć z pliku wartość |%c|, a odczytała |%c|", expected_filecontent[1217], c);

            free(filecontent);
            file_close(file);
            fat_close(volume);
            disk_close(disk);

            test_no_heap_leakage();
            onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)
        
    //
    // -----------
    //

    // przywrócenie podstawowych parametów przydzielania zasobów (jeśli to tylko możliwe)
    rldebug_reset_limits();
    test_file_write_limit_restore();
    
    test_ok();
}

//
//  Test 30: Sprawdzanie poprawności działania funkcji file_seek
//
void UTEST30(void)
{
    // informacje o teście
    test_start(30, "Sprawdzanie poprawności działania funkcji file_seek", __LINE__);

    // uwarunkowanie zasobów - pamięci, itd...
    test_file_write_limit_setup(33554432);
    rldebug_reset_limits();
    
    //
    // -----------
    //
    
            char *filecontent = (char *)calloc(3421, 1);
            char expected_filecontent[3422] = "";

            strcat(expected_filecontent, "His wings are pointed, for there always throng\nAll such as not to Archeron descend.\"\n     Then I: \"If new laws have not quite destroy\'d\nMemory and use of that sweet song of love,\nThat while all my cares had power to \'swage;\nPlease thee with it a little to console\nMy spirit, that incumber\'d with its frame,\nTravelling so far, of pain is overcome.\"\n     \"Love that discourses in my thoughts.\"  He then\nBegan in such soft accents, that within\nThe sweetness thrills me yet.  My gentle guide\nAnd all who came with him, so well were pleas\'d,\nThat seem\'d naught else might in their thoughts have room.\n     Fast fix\'d in mute attention to his notes\nWe stood, when lo!  that old man venerable\nExclaiming, \"How is this, ye tardy spirits?\nWhat negligence detains you loit\'ring here?\nRun to the mountain to cast off those scales,\nThat from your eyes the sight of God conceal.\"\n     As a wild flock of pigeons, to their food\nCollected, blade or tares, without their pride\nAccustom\'d, and in still and quiet sort,\nIf aught alarm them, suddenly desert\nTheir meal, assail\'d by more important care;\nSo I that new-come troop beheld, the song\nDeserting, hasten to the mountain\'s side,\nAs one who goes yet where he tends knows not.\n     Nor with less hurried step did we depart.\n\n\n\nCANTO III\n\nThem sudden flight had scatter\'d over the plain,\nTurn\'d tow\'rds the mountain, whither reason\'s voice\nDrives us; I to my faithful company\nAdhering, left it not.  For how of him\nDepriv\'d, might I have sped, or who beside\nWould o\'er the mountainous tract have led my steps\nHe with the bitter pang of self-remorse\nSeem\'d smitten.  O clear conscience and upright\nHow doth a little fling wound thee sore!\n     Soon as his feet desisted (slack\'ning pace),\nFrom haste, that mars all decency of act,\nMy mind, that in itself before was wrapt,\nIts thoughts expanded, as with joy restor\'d:\nAnd full against the steep ascent I set\nMy face, where highest to heav\'n its top o\'erflows.\n     The sun, that flar\'d behind, with ruddy beam\nBefore my form was broken; for in me\nHis rays resistance met.  I turn\'d aside\nWith fear of being left, when I beheld\nOnly before myself the ground obscur\'d.\nWhen thus my solace, turning him around,\nBespake me kindly:  \"Why distrustest thou?\nBeliev\'st not I am with thee, thy sure guide?\nIt now is evening there, where buried lies\nThe body, in which I cast a shade, remov\'d\nTo Naples from Brundusium\'s wall.  Nor thou\nMarvel, if before me no shadow fall,\nMore than that in the sky element\nOne ray obstructs not other.  To endure\nTorments of heat and cold extreme, like frames\nThat virtue hath dispos\'d, which how it works\nWills not to us should be reveal\'d.  Insane\nWho hopes, our reason may that space explore,\nWhich holds three persons in one substance knit.\nSeek not the wherefore, race of human kind;\nCould ye have seen the whole, no need had been\nFor Mary to bring forth.  Moreover ye\nHave seen such men desiring fruitlessly;\nTo whose desires repose would have been giv\'n,\nThat now but serve them for eternal grief.\nI speak of Plato, and the Stagyrite,\nAnd others many more.\"  And then he bent\nDownwards his forehead, and in troubled mood\nBroke off his speech.  Meanwhile we had arriv\'d\nFar as the mountain\'s foot, and there the rock\nFound of so steep ascent, that nimblest steps\nTo climb it had been vain.  The most remote\nMost wild untrodden path, in all the tract\n\'Twixt Lerice and Turbia were to this\nA ladder easy\' an");

            struct disk_t* disk = disk_open_from_file("subtract_fat12_volume.img");
            test_error(disk != NULL, "Funkcja disk_open_from_file() niepoprawnie otworzyła plik");
            onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)

            struct volume_t* volume = fat_open(disk, 0);
            test_error(volume != NULL, "Funkcja fat_open() niepoprawnie otworzyła wolumin");
            onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)

            struct file_t* file = file_open(volume, "TAIL");
            test_error(file != NULL, "Funkcja file_open() niepoprawnie otworzyła plik");
            onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)

            file_seek(file, -3296, SEEK_END);

            char c;
            int res = file_read(&c, 1, 1, file);
            test_error(res == 1, "Funkcja file_read() powinna zwrócić wartość 1, a zwróciła %d", res);
            onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)
            test_error(expected_filecontent[125] == c, "Funkcja file_read() powinna odczyatć z pliku wartość |%c|, a odczytała |%c|", expected_filecontent[125], c);

            free(filecontent);
            file_close(file);
            fat_close(volume);
            disk_close(disk);

            test_no_heap_leakage();
            onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)
        
    //
    // -----------
    //

    // przywrócenie podstawowych parametów przydzielania zasobów (jeśli to tylko możliwe)
    rldebug_reset_limits();
    test_file_write_limit_restore();
    
    test_ok();
}

//
//  Test 31: Sprawdzanie poprawności działania funkcji file_seek
//
void UTEST31(void)
{
    // informacje o teście
    test_start(31, "Sprawdzanie poprawności działania funkcji file_seek", __LINE__);

    // uwarunkowanie zasobów - pamięci, itd...
    test_file_write_limit_setup(33554432);
    rldebug_reset_limits();
    
    //
    // -----------
    //
    
            char *filecontent = (char *)calloc(3027, 1);
            char expected_filecontent[3028] = "";

            strcat(expected_filecontent, "onferred by that family on our poet at a subsequent perid of his\nexile in 1307.\n\n\n\nCanto XXV\n\nv.1.  The sinner ]  So Trissino\n        Poi facea con le man le fiche al cielo\n        Dicendo:  Togli, Iddio; che puoi piu farmi?\n               L\'ital. Lib. c. xii\n\nv. 12.  Thy seed]  Thy ancestry.\n\nv. 15.  Not him]  Capanaeus.  Canto XIV.\n\nv. 18.  On Marenna\'s marsh.]  An extensive tract near the\nsea-shore in Tuscany.\n\nv. 24.  Cacus.]  Virgil, Aen. l. viii. 193.\n\nv. 31.  A hundred blows.]  Less than ten blows, out of the\nhundred Hercules gave him, deprived him of feeling.\n\nv. 39.  Cianfa]  He is said to have been of the family of Donati\nat Florence.\n\nv. 57.  Thus up the shrinking paper.]\n        --All my bowels crumble up to dust.\n        I am a scribbled form, drawn up with a pen\n        Upon a parchment; and against this fire\n        Do I shrink up.\n               Shakespeare, K. John, a. v. s. 7.\n\nv. 61.  Agnello.]  Agnello Brunelleschi\n\nv. 77.  In that part.]  The navel.\n\nv. 81.  As if by sleep or fev\'rous fit assail\'d.]\n               O Rome!  thy head\n        Is drown\'d in sleep, and all thy body fev\'ry.\n               Ben Jonson\'s Catiline.\n\nv. 85.  Lucan.]  Phars. l. ix. 766 and 793.\n\nv. 87.  Ovid.] Metam. l. iv. and v.\n\nv. 121.  His sharpen\'d visage.]  Compare Milton, P. L. b. x. 511\n&c.\n\nv. 131.  Buoso.]  He is said to have been of the Donati family.\n\nv. 138.  Sciancato.]  Puccio Sciancato, a noted robber, whose\nfamilly, Venturi says, he has not been able to discover.\n\nv. 140.  Gaville.]  Francesco Guercio Cavalcante was killed at\nGaville, near Florence; and in revenge of his death several\ninhabitants of that district were put to death.\n\nCANTO XXVI\n\nv. 7. But if our minds.]\n\n        Namque sub Auroram, jam dormitante lucerna,\n        Somnia quo cerni tempore vera solent.\n               Ovid, Epist. xix\n\nThe same poetical superstition is alluded to in the Purgatory,\nCant. IX. and XXVII.\n\nv. 9. Shall feel what Prato.]  The poet prognosticates the\ncalamities which were soon to befal his native city, and which he\nsays, even her nearest neighbor, Prato, would wish her.  The\ncalamities more particularly pointed at, are said to be the fall\nof a wooden bridge over the Arno, in May, 1304, where a large\nmultitude were assembled to witness a representation  of hell nnd\nthe infernal torments, in consequence of which accident many\nlives were lost; and a conflagration that in the following month\ndestroyed more than seventeen hundred houses, many ofthem\nsumptuous buildings.  See G. Villani, Hist. l. viii. c. 70 and\n71.\n\nv. 22.  More than I am wont.]  \"When I reflect on the punishment\nallotted to those who do not give sincere and upright advice to\nothers I am more anxious than ever not to abuse to so bad a\npurpose those talents, whatever they may be, which Nature, or\nrather Providence, has conferred on me.\"  It is probable that\nthis declaration was the result of real feeling Textd have\ngiven great weight to\nany opinion or party he had espoused, and to whom indigence and\nexile might h");

            struct disk_t* disk = disk_open_from_file("subtract_fat12_volume.img");
            test_error(disk != NULL, "Funkcja disk_open_from_file() niepoprawnie otworzyła plik");
            onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)

            struct volume_t* volume = fat_open(disk, 0);
            test_error(volume != NULL, "Funkcja fat_open() niepoprawnie otworzyła wolumin");
            onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)

            struct file_t* file = file_open(volume, "LIFE");
            test_error(file != NULL, "Funkcja file_open() niepoprawnie otworzyła plik");
            onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)

            file_seek(file, 1383, SEEK_SET);
            file_seek(file, 920, SEEK_CUR);

            char c;
            int res = file_read(&c, 1, 1, file);
            test_error(res == 1, "Funkcja file_read() powinna zwrócić wartość 1, a zwróciła %d", res);
            onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)
            test_error(expected_filecontent[2303] == c, "Funkcja file_read() powinna odczyatć z pliku wartość |%c|, a odczytała |%c|", expected_filecontent[2303], c);

            free(filecontent);
            file_close(file);
            fat_close(volume);
            disk_close(disk);

            test_no_heap_leakage();
            onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)
        
    //
    // -----------
    //

    // przywrócenie podstawowych parametów przydzielania zasobów (jeśli to tylko możliwe)
    rldebug_reset_limits();
    test_file_write_limit_restore();
    
    test_ok();
}

//
//  Test 32: Sprawdzanie poprawności działania funkcji file_open
//
void UTEST32(void)
{
    // informacje o teście
    test_start(32, "Sprawdzanie poprawności działania funkcji file_open", __LINE__);

    // uwarunkowanie zasobów - pamięci, itd...
    test_file_write_limit_setup(33554432);
    rldebug_reset_limits();
    
    //
    // -----------
    //
    

                 struct disk_t* disk = disk_open_from_file("subtract_fat12_volume.img");
                 test_error(disk != NULL, "Funkcja disk_open_from_file() niepoprawnie otworzyła plik");
                 onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)

                 struct volume_t* volume = fat_open(disk, 0);
                 test_error(volume != NULL, "Funkcja fat_open() niepoprawnie otworzyła wolumin");
                 onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)

                 struct file_t* file = file_open(volume, "SOFT");
                 test_error(file == NULL, "Funkcja file_open() powinna zwrócić NULL - nazwa podana w parametrze (SOFT) jest nazwą katalogu, a nie pliku");
                 onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)

                 fat_close(volume);
                 disk_close(disk);

                 test_no_heap_leakage();
                 onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)
             
    //
    // -----------
    //

    // przywrócenie podstawowych parametów przydzielania zasobów (jeśli to tylko możliwe)
    rldebug_reset_limits();
    test_file_write_limit_restore();
    
    test_ok();
}

//
//  Test 33: Sprawdzanie poprawności działania funkcji file_open
//
void UTEST33(void)
{
    // informacje o teście
    test_start(33, "Sprawdzanie poprawności działania funkcji file_open", __LINE__);

    // uwarunkowanie zasobów - pamięci, itd...
    test_file_write_limit_setup(33554432);
    rldebug_reset_limits();
    
    //
    // -----------
    //
    

                 struct disk_t* disk = disk_open_from_file("subtract_fat12_volume.img");
                 test_error(disk != NULL, "Funkcja disk_open_from_file() niepoprawnie otworzyła plik");
                 onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)

                 struct volume_t* volume = fat_open(disk, 0);
                 test_error(volume != NULL, "Funkcja fat_open() niepoprawnie otworzyła wolumin");
                 onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)

                 struct file_t* file = file_open(volume, "PAST");
                 test_error(file == NULL, "Funkcja file_open() powinna zwrócić NULL - nazwa podana w parametrze (PAST) jest nazwą katalogu, a nie pliku");
                 onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)

                 fat_close(volume);
                 disk_close(disk);

                 test_no_heap_leakage();
                 onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)
             
    //
    // -----------
    //

    // przywrócenie podstawowych parametów przydzielania zasobów (jeśli to tylko możliwe)
    rldebug_reset_limits();
    test_file_write_limit_restore();
    
    test_ok();
}

//
//  Test 34: Sprawdzanie poprawności działania funkcji file_open
//
void UTEST34(void)
{
    // informacje o teście
    test_start(34, "Sprawdzanie poprawności działania funkcji file_open", __LINE__);

    // uwarunkowanie zasobów - pamięci, itd...
    test_file_write_limit_setup(33554432);
    rldebug_reset_limits();
    
    //
    // -----------
    //
    

                 struct disk_t* disk = disk_open_from_file("subtract_fat12_volume.img");
                 test_error(disk != NULL, "Funkcja disk_open_from_file() niepoprawnie otworzyła plik");
                 onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)

                 struct volume_t* volume = fat_open(disk, 0);
                 test_error(volume != NULL, "Funkcja fat_open() niepoprawnie otworzyła wolumin");
                 onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)

                 struct file_t* file = file_open(volume, "THOSE");
                 test_error(file == NULL, "Funkcja file_open() powinna zwrócić NULL - nazwa podana w parametrze (THOSE) jest nazwą katalogu, a nie pliku");
                 onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)

                 fat_close(volume);
                 disk_close(disk);

                 test_no_heap_leakage();
                 onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)
             
    //
    // -----------
    //

    // przywrócenie podstawowych parametów przydzielania zasobów (jeśli to tylko możliwe)
    rldebug_reset_limits();
    test_file_write_limit_restore();
    
    test_ok();
}

//
//  Test 35: Sprawdzanie poprawności działania funkcji file_open
//
void UTEST35(void)
{
    // informacje o teście
    test_start(35, "Sprawdzanie poprawności działania funkcji file_open", __LINE__);

    // uwarunkowanie zasobów - pamięci, itd...
    test_file_write_limit_setup(33554432);
    rldebug_reset_limits();
    
    //
    // -----------
    //
    

                 struct disk_t* disk = disk_open_from_file("subtract_fat12_volume.img");
                 test_error(disk != NULL, "Funkcja disk_open_from_file() niepoprawnie otworzyła plik");
                 onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)

                 struct volume_t* volume = fat_open(disk, 0);
                 test_error(volume != NULL, "Funkcja fat_open() niepoprawnie otworzyła wolumin");
                 onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)

                 struct file_t* file = file_open(volume, "HERE");
                 test_error(file == NULL, "Funkcja file_open() powinna zwrócić NULL - nazwa podana w parametrze (HERE) jest nazwą katalogu, a nie pliku");
                 onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)

                 fat_close(volume);
                 disk_close(disk);

                 test_no_heap_leakage();
                 onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)
             
    //
    // -----------
    //

    // przywrócenie podstawowych parametów przydzielania zasobów (jeśli to tylko możliwe)
    rldebug_reset_limits();
    test_file_write_limit_restore();
    
    test_ok();
}

//
//  Test 36: Sprawdzanie poprawności działania funkcji file_open
//
void UTEST36(void)
{
    // informacje o teście
    test_start(36, "Sprawdzanie poprawności działania funkcji file_open", __LINE__);

    // uwarunkowanie zasobów - pamięci, itd...
    test_file_write_limit_setup(33554432);
    rldebug_reset_limits();
    
    //
    // -----------
    //
    

                 struct disk_t* disk = disk_open_from_file("subtract_fat12_volume.img");
                 test_error(disk != NULL, "Funkcja disk_open_from_file() niepoprawnie otworzyła plik");
                 onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)

                 struct volume_t* volume = fat_open(disk, 0);
                 test_error(volume != NULL, "Funkcja fat_open() niepoprawnie otworzyła wolumin");
                 onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)

                 struct file_t* file = file_open(volume, "BUILD");
                 test_error(file == NULL, "Funkcja file_open() powinna zwrócić NULL - nazwa podana w parametrze (BUILD) jest nazwą katalogu, a nie pliku");
                 onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)

                 fat_close(volume);
                 disk_close(disk);

                 test_no_heap_leakage();
                 onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)
             
    //
    // -----------
    //

    // przywrócenie podstawowych parametów przydzielania zasobów (jeśli to tylko możliwe)
    rldebug_reset_limits();
    test_file_write_limit_restore();
    
    test_ok();
}

//
//  Test 37: Sprawdzanie poprawności działania funkcji file_open
//
void UTEST37(void)
{
    // informacje o teście
    test_start(37, "Sprawdzanie poprawności działania funkcji file_open", __LINE__);

    // uwarunkowanie zasobów - pamięci, itd...
    test_file_write_limit_setup(33554432);
    rldebug_reset_limits();
    
    //
    // -----------
    //
    

                 struct disk_t* disk = disk_open_from_file("subtract_fat12_volume.img");
                 test_error(disk != NULL, "Funkcja disk_open_from_file() niepoprawnie otworzyła plik");
                 onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)

                 struct volume_t* volume = fat_open(disk, 0);
                 test_error(volume != NULL, "Funkcja fat_open() niepoprawnie otworzyła wolumin");
                 onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)

                 struct file_t* file = file_open(volume, "PAY");
                 test_error(file == NULL, "Funkcja file_open() powinna zwrócić NULL - nazwa podana w parametrze (PAY) jest nazwą katalogu, a nie pliku");
                 onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)

                 fat_close(volume);
                 disk_close(disk);

                 test_no_heap_leakage();
                 onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)
             
    //
    // -----------
    //

    // przywrócenie podstawowych parametów przydzielania zasobów (jeśli to tylko możliwe)
    rldebug_reset_limits();
    test_file_write_limit_restore();
    
    test_ok();
}

//
//  Test 38: Sprawdzanie poprawności działania funkcji file_open
//
void UTEST38(void)
{
    // informacje o teście
    test_start(38, "Sprawdzanie poprawności działania funkcji file_open", __LINE__);

    // uwarunkowanie zasobów - pamięci, itd...
    test_file_write_limit_setup(33554432);
    rldebug_reset_limits();
    
    //
    // -----------
    //
    

                 struct disk_t* disk = disk_open_from_file("subtract_fat12_volume.img");
                 test_error(disk != NULL, "Funkcja disk_open_from_file() niepoprawnie otworzyła plik");
                 onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)

                 struct volume_t* volume = fat_open(disk, 0);
                 test_error(volume != NULL, "Funkcja fat_open() niepoprawnie otworzyła wolumin");
                 onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)

                 struct file_t* file = file_open(volume, "CHIEF");
                 test_error(file == NULL, "Funkcja file_open() powinna zwrócić NULL - nazwa podana w parametrze (CHIEF) jest nazwą katalogu, a nie pliku");
                 onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)

                 fat_close(volume);
                 disk_close(disk);

                 test_no_heap_leakage();
                 onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)
             
    //
    // -----------
    //

    // przywrócenie podstawowych parametów przydzielania zasobów (jeśli to tylko możliwe)
    rldebug_reset_limits();
    test_file_write_limit_restore();
    
    test_ok();
}

//
//  Test 39: Sprawdzanie poprawności działania funkcji file_open
//
void UTEST39(void)
{
    // informacje o teście
    test_start(39, "Sprawdzanie poprawności działania funkcji file_open", __LINE__);

    // uwarunkowanie zasobów - pamięci, itd...
    test_file_write_limit_setup(33554432);
    rldebug_reset_limits();
    
    //
    // -----------
    //
    

                 struct disk_t* disk = disk_open_from_file("subtract_fat12_volume.img");
                 test_error(disk != NULL, "Funkcja disk_open_from_file() niepoprawnie otworzyła plik");
                 onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)

                 struct volume_t* volume = fat_open(disk, 0);
                 test_error(volume != NULL, "Funkcja fat_open() niepoprawnie otworzyła wolumin");
                 onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)

                 struct file_t* file = file_open(volume, "GENTLESE");
                 test_error(file == NULL, "Funkcja file_open() powinna zwrócić NULL - nazwa podana w parametrze (GENTLESE) jest nazwą katalogu, a nie pliku");
                 onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)

                 fat_close(volume);
                 disk_close(disk);

                 test_no_heap_leakage();
                 onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)
             
    //
    // -----------
    //

    // przywrócenie podstawowych parametów przydzielania zasobów (jeśli to tylko możliwe)
    rldebug_reset_limits();
    test_file_write_limit_restore();
    
    test_ok();
}

//
//  Test 40: Sprawdzanie poprawności działania funkcji file_open
//
void UTEST40(void)
{
    // informacje o teście
    test_start(40, "Sprawdzanie poprawności działania funkcji file_open", __LINE__);

    // uwarunkowanie zasobów - pamięci, itd...
    test_file_write_limit_setup(33554432);
    rldebug_reset_limits();
    
    //
    // -----------
    //
    

            struct disk_t* disk = disk_open_from_file("subtract_fat12_volume.img");
            test_error(disk != NULL, "Funkcja disk_open_from_file() niepoprawnie otworzyła plik");
            onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)

            struct volume_t* volume = fat_open(disk, 0);
            test_error(volume != NULL, "Funkcja fat_open() niepoprawnie otworzyła wolumin");
            onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)

            struct file_t* file = file_open(volume, "GOLD");
            test_error(file == NULL, "Funkcja file_open() nie powinna otworzyć pliku o nazwie GOLD, ponieważ nie istnieje on w katalogu głównym");
            onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)

            fat_close(volume);
            disk_close(disk);

            test_no_heap_leakage();
            onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)
        
    //
    // -----------
    //

    // przywrócenie podstawowych parametów przydzielania zasobów (jeśli to tylko możliwe)
    rldebug_reset_limits();
    test_file_write_limit_restore();
    
    test_ok();
}

//
//  Test 41: Sprawdzanie poprawności działania funkcji file_read
//
void UTEST41(void)
{
    // informacje o teście
    test_start(41, "Sprawdzanie poprawności działania funkcji file_read", __LINE__);

    // uwarunkowanie zasobów - pamięci, itd...
    test_file_write_limit_setup(33554432);
    rldebug_reset_limits();
    
    //
    // -----------
    //
    

            struct disk_t* disk = disk_open_from_file("subtract_fat12_volume.img");
            test_error(disk != NULL, "Funkcja disk_open_from_file() niepoprawnie otworzyła plik");
            onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)

            struct volume_t* volume = fat_open(disk, 0);
            test_error(volume != NULL, "Funkcja fat_open() niepoprawnie otworzyła wolumin");
            onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)

            struct file_t* file = file_open(NULL, "GOLD");
            test_error(file == NULL, "Funkcja file_open() powinna zwrócić NULL w przypadku podania błędnych danych");
            onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)

            fat_close(volume);
            disk_close(disk);

            test_no_heap_leakage();
            onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)
        
    //
    // -----------
    //

    // przywrócenie podstawowych parametów przydzielania zasobów (jeśli to tylko możliwe)
    rldebug_reset_limits();
    test_file_write_limit_restore();
    
    test_ok();
}

//
//  Test 42: Sprawdzanie poprawności działania funkcji file_read
//
void UTEST42(void)
{
    // informacje o teście
    test_start(42, "Sprawdzanie poprawności działania funkcji file_read", __LINE__);

    // uwarunkowanie zasobów - pamięci, itd...
    test_file_write_limit_setup(33554432);
    rldebug_reset_limits();
    
    //
    // -----------
    //
    

            struct disk_t* disk = disk_open_from_file("subtract_fat12_volume.img");
            test_error(disk != NULL, "Funkcja disk_open_from_file() niepoprawnie otworzyła plik");
            onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)

            struct volume_t* volume = fat_open(disk, 0);
            test_error(volume != NULL, "Funkcja fat_open() niepoprawnie otworzyła wolumin");
            onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)

            struct file_t* file = file_open(volume, NULL);
            test_error(file == NULL, "Funkcja file_open() powinna zwrócić NULL w przypadku podania błędnych danych");
            onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)

            fat_close(volume);
            disk_close(disk);

            test_no_heap_leakage();
            onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)
        
    //
    // -----------
    //

    // przywrócenie podstawowych parametów przydzielania zasobów (jeśli to tylko możliwe)
    rldebug_reset_limits();
    test_file_write_limit_restore();
    
    test_ok();
}

//
//  Test 43: Sprawdzanie poprawności działania funkcji file_read
//
void UTEST43(void)
{
    // informacje o teście
    test_start(43, "Sprawdzanie poprawności działania funkcji file_read", __LINE__);

    // uwarunkowanie zasobów - pamięci, itd...
    test_file_write_limit_setup(33554432);
    rldebug_reset_limits();
    
    //
    // -----------
    //
    

            struct disk_t* disk = disk_open_from_file("subtract_fat12_volume.img");
            test_error(disk != NULL, "Funkcja disk_open_from_file() niepoprawnie otworzyła plik");
            onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)

            struct volume_t* volume = fat_open(disk, 0);
            test_error(volume != NULL, "Funkcja fat_open() niepoprawnie otworzyła wolumin");
            onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)

            struct file_t* file = file_open(NULL, NULL);
            test_error(file == NULL, "Funkcja file_open() powinna zwrócić NULL w przypadku podania błędnych danych");
            onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)

            fat_close(volume);
            disk_close(disk);

            test_no_heap_leakage();
            onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)
        
    //
    // -----------
    //

    // przywrócenie podstawowych parametów przydzielania zasobów (jeśli to tylko możliwe)
    rldebug_reset_limits();
    test_file_write_limit_restore();
    
    test_ok();
}

//
//  Test 44: Sprawdzanie poprawności działania funkcji file_close
//
void UTEST44(void)
{
    // informacje o teście
    test_start(44, "Sprawdzanie poprawności działania funkcji file_close", __LINE__);

    // uwarunkowanie zasobów - pamięci, itd...
    test_file_write_limit_setup(33554432);
    rldebug_reset_limits();
    
    //
    // -----------
    //
    

            file_close(NULL);

            test_no_heap_leakage();
            onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)
        
    //
    // -----------
    //

    // przywrócenie podstawowych parametów przydzielania zasobów (jeśli to tylko możliwe)
    rldebug_reset_limits();
    test_file_write_limit_restore();
    
    test_ok();
}

//
//  Test 45: Sprawdzanie poprawności działania funkcji file_read
//
void UTEST45(void)
{
    // informacje o teście
    test_start(45, "Sprawdzanie poprawności działania funkcji file_read", __LINE__);

    // uwarunkowanie zasobów - pamięci, itd...
    test_file_write_limit_setup(33554432);
    rldebug_reset_limits();
    
    //
    // -----------
    //
    

            struct disk_t* disk = disk_open_from_file("subtract_fat12_volume.img");
            test_error(disk != NULL, "Funkcja disk_open_from_file() niepoprawnie otworzyła plik");
            onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)

            struct volume_t* volume = fat_open(disk, 0);
            test_error(volume != NULL, "Funkcja fat_open() niepoprawnie otworzyła wolumin");
            onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)

            struct file_t* file = file_open(volume, "TAIL");
            test_error(file != NULL, "Funkcja file_open() niepoprawnie otworzyła plik");
            onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)

            int res = file_read(NULL, 1, 1, file);
            test_error(res == -1, "Funkcja file_read() powinna zwrócić wartość -1, a zwróciła %d", res);
            onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)

            file_close(file);
            fat_close(volume);
            disk_close(disk);

            test_no_heap_leakage();
            onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)
        
    //
    // -----------
    //

    // przywrócenie podstawowych parametów przydzielania zasobów (jeśli to tylko możliwe)
    rldebug_reset_limits();
    test_file_write_limit_restore();
    
    test_ok();
}

//
//  Test 46: Sprawdzanie poprawności działania funkcji dir_read
//
void UTEST46(void)
{
    // informacje o teście
    test_start(46, "Sprawdzanie poprawności działania funkcji dir_read", __LINE__);

    // uwarunkowanie zasobów - pamięci, itd...
    test_file_write_limit_setup(33554432);
    rldebug_reset_limits();
    
    //
    // -----------
    //
    

            char* expected_names[15] = { "TAIL", "MULTIPLY.BIN", "THOUSAND.TXT", "LIFE", "WHO.TX", "AIR.BIN", "FORM.BIN", "SOFT", "PAST", "THOSE", "HERE", "BUILD", "PAY", "CHIEF", "GENTLESE" };
            int found_names[15] = { 0 };

            struct disk_t* disk = disk_open_from_file("subtract_fat12_volume.img");
            test_error(disk != NULL, "Funkcja disk_open_from_file() niepoprawnie otworzyła plik");
            onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)

            struct volume_t* volume = fat_open(disk, 0);
            test_error(volume != NULL, "Funkcja fat_open() niepoprawnie otworzyła wolumin");
            onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)

            struct dir_t* pdir = dir_open(volume, "\\");
            test_error(pdir != NULL, "Funkcja dir_open() niepoprawnie otworzyła katalog");
            onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)

            for (int i = 0; i < 15; ++i)
            {
                struct dir_entry_t entry;
                int res = dir_read(pdir, &entry);
                test_error(res == 0, "Funkcja dir_read() niepoprawnie odczytała wpis z katalogu");
                onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)

                int name_found = 0;

                for (int j = 0; j < 15; ++j)
                {
                    if (strcmp(entry.name, expected_names[j]) == 0)
                    {
                        test_error(found_names[j] == 0, "Funkcja dir_read() ponownie zwróciła informację o wpisie %s", expected_names[j]);
                        found_names[j] = 1;
                        name_found = 1;
                        break;
                    }
                }

                test_error(name_found == 1, "Funkcja dir_read() zwróciła informację o wpisie %s, który nie znajduje się w katalogu", entry.name);
            }

            struct dir_entry_t entry;
            int res = dir_read(pdir, &entry);
            test_error(res == 1, "Funkcja dir_read() zwróciła niepoprawną wartość, po odczytaniu wszystkich wpisów z katalogu powinna zwrócić %d, a zwróciła %d", 1, res);
            onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)

            dir_close(pdir);
            fat_close(volume);
            disk_close(disk);

            test_no_heap_leakage();
            onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)
        
    //
    // -----------
    //

    // przywrócenie podstawowych parametów przydzielania zasobów (jeśli to tylko możliwe)
    rldebug_reset_limits();
    test_file_write_limit_restore();
    
    test_ok();
}

//
//  Test 47: Sprawdzanie poprawności działania funkcji dir_open
//
void UTEST47(void)
{
    // informacje o teście
    test_start(47, "Sprawdzanie poprawności działania funkcji dir_open", __LINE__);

    // uwarunkowanie zasobów - pamięci, itd...
    test_file_write_limit_setup(33554432);
    rldebug_reset_limits();
    
    //
    // -----------
    //
    

                struct disk_t* disk = disk_open_from_file("subtract_fat12_volume.img");
                test_error(disk != NULL, "Funkcja disk_open_from_file() niepoprawnie otworzyła plik");
                onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)

                struct volume_t* volume = fat_open(disk, 0);
                test_error(volume != NULL, "Funkcja fat_open() niepoprawnie otworzyła wolumin");
                onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)

                struct dir_t*  dir = dir_open(volume, "TAIL");
                test_error(dir == NULL, "Funkcja dir_open() powinna zwrócić NULL w przypadku podania niepoprawnej nazwy katalogu");
                onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)

                fat_close(volume);
                disk_close(disk);

                test_no_heap_leakage();
                onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)
            
    //
    // -----------
    //

    // przywrócenie podstawowych parametów przydzielania zasobów (jeśli to tylko możliwe)
    rldebug_reset_limits();
    test_file_write_limit_restore();
    
    test_ok();
}

//
//  Test 48: Sprawdzanie poprawności działania funkcji dir_open
//
void UTEST48(void)
{
    // informacje o teście
    test_start(48, "Sprawdzanie poprawności działania funkcji dir_open", __LINE__);

    // uwarunkowanie zasobów - pamięci, itd...
    test_file_write_limit_setup(33554432);
    rldebug_reset_limits();
    
    //
    // -----------
    //
    

                struct disk_t* disk = disk_open_from_file("subtract_fat12_volume.img");
                test_error(disk != NULL, "Funkcja disk_open_from_file() niepoprawnie otworzyła plik");
                onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)

                struct volume_t* volume = fat_open(disk, 0);
                test_error(volume != NULL, "Funkcja fat_open() niepoprawnie otworzyła wolumin");
                onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)

                struct dir_t*  dir = dir_open(volume, "MULTIPLY.BIN");
                test_error(dir == NULL, "Funkcja dir_open() powinna zwrócić NULL w przypadku podania niepoprawnej nazwy katalogu");
                onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)

                fat_close(volume);
                disk_close(disk);

                test_no_heap_leakage();
                onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)
            
    //
    // -----------
    //

    // przywrócenie podstawowych parametów przydzielania zasobów (jeśli to tylko możliwe)
    rldebug_reset_limits();
    test_file_write_limit_restore();
    
    test_ok();
}

//
//  Test 49: Sprawdzanie poprawności działania funkcji dir_open
//
void UTEST49(void)
{
    // informacje o teście
    test_start(49, "Sprawdzanie poprawności działania funkcji dir_open", __LINE__);

    // uwarunkowanie zasobów - pamięci, itd...
    test_file_write_limit_setup(33554432);
    rldebug_reset_limits();
    
    //
    // -----------
    //
    

                struct disk_t* disk = disk_open_from_file("subtract_fat12_volume.img");
                test_error(disk != NULL, "Funkcja disk_open_from_file() niepoprawnie otworzyła plik");
                onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)

                struct volume_t* volume = fat_open(disk, 0);
                test_error(volume != NULL, "Funkcja fat_open() niepoprawnie otworzyła wolumin");
                onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)

                struct dir_t*  dir = dir_open(volume, "THOUSAND.TXT");
                test_error(dir == NULL, "Funkcja dir_open() powinna zwrócić NULL w przypadku podania niepoprawnej nazwy katalogu");
                onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)

                fat_close(volume);
                disk_close(disk);

                test_no_heap_leakage();
                onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)
            
    //
    // -----------
    //

    // przywrócenie podstawowych parametów przydzielania zasobów (jeśli to tylko możliwe)
    rldebug_reset_limits();
    test_file_write_limit_restore();
    
    test_ok();
}

//
//  Test 50: Sprawdzanie poprawności działania funkcji dir_open
//
void UTEST50(void)
{
    // informacje o teście
    test_start(50, "Sprawdzanie poprawności działania funkcji dir_open", __LINE__);

    // uwarunkowanie zasobów - pamięci, itd...
    test_file_write_limit_setup(33554432);
    rldebug_reset_limits();
    
    //
    // -----------
    //
    

                struct disk_t* disk = disk_open_from_file("subtract_fat12_volume.img");
                test_error(disk != NULL, "Funkcja disk_open_from_file() niepoprawnie otworzyła plik");
                onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)

                struct volume_t* volume = fat_open(disk, 0);
                test_error(volume != NULL, "Funkcja fat_open() niepoprawnie otworzyła wolumin");
                onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)

                struct dir_t*  dir = dir_open(volume, "LIFE");
                test_error(dir == NULL, "Funkcja dir_open() powinna zwrócić NULL w przypadku podania niepoprawnej nazwy katalogu");
                onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)

                fat_close(volume);
                disk_close(disk);

                test_no_heap_leakage();
                onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)
            
    //
    // -----------
    //

    // przywrócenie podstawowych parametów przydzielania zasobów (jeśli to tylko możliwe)
    rldebug_reset_limits();
    test_file_write_limit_restore();
    
    test_ok();
}

//
//  Test 51: Sprawdzanie poprawności działania funkcji dir_open
//
void UTEST51(void)
{
    // informacje o teście
    test_start(51, "Sprawdzanie poprawności działania funkcji dir_open", __LINE__);

    // uwarunkowanie zasobów - pamięci, itd...
    test_file_write_limit_setup(33554432);
    rldebug_reset_limits();
    
    //
    // -----------
    //
    

                struct disk_t* disk = disk_open_from_file("subtract_fat12_volume.img");
                test_error(disk != NULL, "Funkcja disk_open_from_file() niepoprawnie otworzyła plik");
                onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)

                struct volume_t* volume = fat_open(disk, 0);
                test_error(volume != NULL, "Funkcja fat_open() niepoprawnie otworzyła wolumin");
                onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)

                struct dir_t*  dir = dir_open(volume, "WHO.TX");
                test_error(dir == NULL, "Funkcja dir_open() powinna zwrócić NULL w przypadku podania niepoprawnej nazwy katalogu");
                onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)

                fat_close(volume);
                disk_close(disk);

                test_no_heap_leakage();
                onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)
            
    //
    // -----------
    //

    // przywrócenie podstawowych parametów przydzielania zasobów (jeśli to tylko możliwe)
    rldebug_reset_limits();
    test_file_write_limit_restore();
    
    test_ok();
}

//
//  Test 52: Sprawdzanie poprawności działania funkcji dir_open
//
void UTEST52(void)
{
    // informacje o teście
    test_start(52, "Sprawdzanie poprawności działania funkcji dir_open", __LINE__);

    // uwarunkowanie zasobów - pamięci, itd...
    test_file_write_limit_setup(33554432);
    rldebug_reset_limits();
    
    //
    // -----------
    //
    

                struct disk_t* disk = disk_open_from_file("subtract_fat12_volume.img");
                test_error(disk != NULL, "Funkcja disk_open_from_file() niepoprawnie otworzyła plik");
                onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)

                struct volume_t* volume = fat_open(disk, 0);
                test_error(volume != NULL, "Funkcja fat_open() niepoprawnie otworzyła wolumin");
                onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)

                struct dir_t*  dir = dir_open(volume, "AIR.BIN");
                test_error(dir == NULL, "Funkcja dir_open() powinna zwrócić NULL w przypadku podania niepoprawnej nazwy katalogu");
                onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)

                fat_close(volume);
                disk_close(disk);

                test_no_heap_leakage();
                onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)
            
    //
    // -----------
    //

    // przywrócenie podstawowych parametów przydzielania zasobów (jeśli to tylko możliwe)
    rldebug_reset_limits();
    test_file_write_limit_restore();
    
    test_ok();
}

//
//  Test 53: Sprawdzanie poprawności działania funkcji dir_open
//
void UTEST53(void)
{
    // informacje o teście
    test_start(53, "Sprawdzanie poprawności działania funkcji dir_open", __LINE__);

    // uwarunkowanie zasobów - pamięci, itd...
    test_file_write_limit_setup(33554432);
    rldebug_reset_limits();
    
    //
    // -----------
    //
    

                struct disk_t* disk = disk_open_from_file("subtract_fat12_volume.img");
                test_error(disk != NULL, "Funkcja disk_open_from_file() niepoprawnie otworzyła plik");
                onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)

                struct volume_t* volume = fat_open(disk, 0);
                test_error(volume != NULL, "Funkcja fat_open() niepoprawnie otworzyła wolumin");
                onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)

                struct dir_t*  dir = dir_open(volume, "FORM.BIN");
                test_error(dir == NULL, "Funkcja dir_open() powinna zwrócić NULL w przypadku podania niepoprawnej nazwy katalogu");
                onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)

                fat_close(volume);
                disk_close(disk);

                test_no_heap_leakage();
                onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)
            
    //
    // -----------
    //

    // przywrócenie podstawowych parametów przydzielania zasobów (jeśli to tylko możliwe)
    rldebug_reset_limits();
    test_file_write_limit_restore();
    
    test_ok();
}

//
//  Test 54: Sprawdzanie poprawności działania funkcji dir_open
//
void UTEST54(void)
{
    // informacje o teście
    test_start(54, "Sprawdzanie poprawności działania funkcji dir_open", __LINE__);

    // uwarunkowanie zasobów - pamięci, itd...
    test_file_write_limit_setup(33554432);
    rldebug_reset_limits();
    
    //
    // -----------
    //
    

            struct disk_t* disk = disk_open_from_file("subtract_fat12_volume.img");
            test_error(disk != NULL, "Funkcja disk_open_from_file() niepoprawnie otworzyła plik");
            onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)

            struct volume_t* volume = fat_open(disk, 0);
            test_error(volume != NULL, "Funkcja fat_open() niepoprawnie otworzyła wolumin");
            onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)

            struct dir_t*  dir = dir_open(volume, "self");
            test_error(dir == NULL, "Funkcja dir_open() powinna zwrócić NULL w przypadku podania niepoprawnej nazwy katalogu");
            onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)

            fat_close(volume);
            disk_close(disk);

            test_no_heap_leakage();
            onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)
        
    //
    // -----------
    //

    // przywrócenie podstawowych parametów przydzielania zasobów (jeśli to tylko możliwe)
    rldebug_reset_limits();
    test_file_write_limit_restore();
    
    test_ok();
}




enum run_mode_t { rm_normal_with_rld = 0, rm_unit_test = 1, rm_main_test = 2 };

int __wrap_main(volatile int _argc, char** _argv, char** _envp)
{
    int volatile vargc = _argc;
    char ** volatile vargv = _argv, ** volatile venvp = _envp;
	volatile enum run_mode_t run_mode = rm_unit_test; // -1
	volatile int selected_test = -1;

    if (vargc > 1)
	{
	    char* smode = strtok(vargv[1], ",");
	    char* stest = strtok(NULL, "");
		char *errptr = NULL;
		run_mode = (enum run_mode_t)strtol(smode, &errptr, 10);
		if (*errptr == '\x0')
		{
			memmove(vargv + 1, vargv + 2, sizeof(char*) * (vargc - 1));
			vargc--;

			if (stest != NULL)
			{
			    int val = (int)strtol(stest, &errptr, 10);
			    if (*errptr == '\x0')
			        selected_test = val;
			}
		}
	}

    // printf("runmode=%d; selected_test=%d\n", run_mode, selected_test);

    // inicjuj testy jednostkowe
    unit_test_init(run_mode, "unit_test_v2.c");
    test_limit_init();
    rldebug_set_reported_severity_level(MSL_FAILURE);

    if (run_mode == rm_normal_with_rld)
    {
        // konfiguracja ograniczników
        rldebug_reset_limits();
        

        // uruchom funkcję main Studenta a potem wyświetl podsumowanie sterty i zasobów
        volatile int ret_code = rdebug_call_main(tested_main, vargc, vargv, venvp);

        rldebug_reset_limits();
        

        int leaks_detected = rldebug_show_leaked_resources(0);
        if (leaks_detected)
            raise(SIGHEAP);

        return ret_code;
    }

    
    if (run_mode == rm_unit_test)
    {
        test_title("Testy jednostkowe");

        void (*pfcn[])(void) =
        { 
            UTEST1, // Sprawdzanie poprawności działania funkcji disk_open_from_file
            UTEST2, // Sprawdzanie poprawności działania funkcji disk_open_from_file
            UTEST3, // Sprawdzanie poprawności działania funkcji disk_close
            UTEST4, // Sprawdzanie poprawności działania funkcji fat_open
            UTEST5, // Sprawdzanie poprawności działania funkcji disk_open_from_file
            UTEST6, // Sprawdzanie poprawności działania funkcji file_read
            UTEST7, // Sprawdzanie poprawności działania funkcji file_read
            UTEST8, // Sprawdzanie poprawności działania funkcji file_read
            UTEST9, // Sprawdzanie poprawności działania funkcji file_read
            UTEST10, // Sprawdzanie poprawności działania funkcji file_read
            UTEST11, // Sprawdzanie poprawności działania funkcji file_read
            UTEST12, // Sprawdzanie poprawności działania funkcji file_read
            UTEST13, // Sprawdzanie poprawności działania funkcji file_read
            UTEST14, // Sprawdzanie poprawności działania funkcji file_read
            UTEST15, // Sprawdzanie poprawności działania funkcji file_read
            UTEST16, // Sprawdzanie poprawności działania funkcji file_read
            UTEST17, // Sprawdzanie poprawności działania funkcji file_read
            UTEST18, // Sprawdzanie poprawności działania funkcji file_read
            UTEST19, // Sprawdzanie poprawności działania funkcji file_read
            UTEST20, // Sprawdzanie poprawności działania funkcji file_read
            UTEST21, // Sprawdzanie poprawności działania funkcji file_read
            UTEST22, // Sprawdzanie poprawności działania funkcji file_read
            UTEST23, // Sprawdzanie poprawności działania funkcji file_read
            UTEST24, // Sprawdzanie poprawności działania funkcji file_read
            UTEST25, // Sprawdzanie poprawności działania funkcji file_read
            UTEST26, // Sprawdzanie poprawności działania funkcji file_read
            UTEST27, // Sprawdzanie poprawności działania funkcji file_read
            UTEST28, // Sprawdzanie poprawności działania funkcji file_read
            UTEST29, // Sprawdzanie poprawności działania funkcji file_seek
            UTEST30, // Sprawdzanie poprawności działania funkcji file_seek
            UTEST31, // Sprawdzanie poprawności działania funkcji file_seek
            UTEST32, // Sprawdzanie poprawności działania funkcji file_open
            UTEST33, // Sprawdzanie poprawności działania funkcji file_open
            UTEST34, // Sprawdzanie poprawności działania funkcji file_open
            UTEST35, // Sprawdzanie poprawności działania funkcji file_open
            UTEST36, // Sprawdzanie poprawności działania funkcji file_open
            UTEST37, // Sprawdzanie poprawności działania funkcji file_open
            UTEST38, // Sprawdzanie poprawności działania funkcji file_open
            UTEST39, // Sprawdzanie poprawności działania funkcji file_open
            UTEST40, // Sprawdzanie poprawności działania funkcji file_open
            UTEST41, // Sprawdzanie poprawności działania funkcji file_read
            UTEST42, // Sprawdzanie poprawności działania funkcji file_read
            UTEST43, // Sprawdzanie poprawności działania funkcji file_read
            UTEST44, // Sprawdzanie poprawności działania funkcji file_close
            UTEST45, // Sprawdzanie poprawności działania funkcji file_read
            UTEST46, // Sprawdzanie poprawności działania funkcji dir_read
            UTEST47, // Sprawdzanie poprawności działania funkcji dir_open
            UTEST48, // Sprawdzanie poprawności działania funkcji dir_open
            UTEST49, // Sprawdzanie poprawności działania funkcji dir_open
            UTEST50, // Sprawdzanie poprawności działania funkcji dir_open
            UTEST51, // Sprawdzanie poprawności działania funkcji dir_open
            UTEST52, // Sprawdzanie poprawności działania funkcji dir_open
            UTEST53, // Sprawdzanie poprawności działania funkcji dir_open
            UTEST54, // Sprawdzanie poprawności działania funkcji dir_open
            NULL
        };

        for (int idx = 0; pfcn[idx] != NULL && !test_get_session_termination_flag(); idx++)
        {
            if (selected_test == -1 || selected_test == idx + 1)
                pfcn[idx]();

            // limit niezaliczonych testów, po jakim testy jednostkowe zostaną przerwane
            if (test_session_get_fail_count() >= 1000)
                test_terminate_session();
        }


        test_title("RLDebug :: Analiza wycieku zasobów");
        // sprawdź wycieki pamięci
        int leaks_detected = rldebug_show_leaked_resources(1);
        test_set_session_leaks(leaks_detected);

        // poinformuj serwer Mrówka o wyniku testu - podsumowanie
        test_title("Podsumowanie");
        if (selected_test == -1)
            test_summary(54); // wszystkie testy muszą zakończyć się sukcesem
        else
            test_summary(1); // tylko jeden (selected_test) test musi zakończyć się  sukcesem
        return EXIT_SUCCESS;
    }
    

    if (run_mode == rm_main_test)
    {
        test_title("Testy funkcji main()");

        void (*pfcn[])(int, char**, char**) =
        { 
            NULL
        };

        for (volatile int idx = 0; pfcn[idx] != NULL && !test_get_session_termination_flag(); idx++)
        {
            if (selected_test == -1 || selected_test == idx + 1)
                pfcn[idx](vargc, vargv, venvp);

            // limit niezaliczonych testów, po jakim testy jednostkowe zostaną przerwane
            if (test_session_get_fail_count() >= 1000)
                test_terminate_session();
        }


        test_title("RLDebug :: Analiza wycieku zasobów");
        // sprawdź wycieki pamięci
        int leaks_detected = rldebug_show_leaked_resources(1);
        test_set_session_leaks(leaks_detected);

        // poinformuj serwer Mrówka o wyniku testu - podsumowanie
        test_title("Podsumowanie");
        if (selected_test == -1)
            test_summary(0); // wszystkie testy muszą zakończyć się sukcesem
        else
            test_summary(1); // tylko jeden (selected_test) test musi zakończyć się  sukcesem

        return EXIT_SUCCESS;
    }

    printf("*** Nieznana wartość RunMode: %d", (int)run_mode);
    abort();
}