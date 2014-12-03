<?php

/**
 * Memeriksa kelengkapan dokumen calon mahasiswa
 * berdasarkan jalur yang dipilih
 *
 * @param $UID
 *  User ID
 * @param $jalur_masuk
 *   String di antara value ini: 'usm','rapor',atau 'un'
 * @return
 *   TRUE or FALSE. TRUE artinya dokumen lengkap.
 */
function admission_user_cek_syarat($uid, $jalur_masuk){
    $profile = profile2_load_by_user($uid);
    
    //untuk jalur USM
    if($jalur_masuk == 'usm' &&
            isset($profile['persyaratan']->field_syarat_usm['und'])){
        
        //jika semua syarata ada (jumlahnya 4) maka return TRUE
        if(count($profile['persyaratan']->field_syarat_usm['und']) == 4){
            return TRUE;
        }
    }
    
    //untuk jalur RAPOR
    if($jalur_masuk == 'rapor' &&
            isset($profile['persyaratan']->field_syarat_jalur_rapor['und'])){
        
        $syarat_array = $profile['persyaratan']->field_syarat_jalur_rapor['und'];
        
        //periksa apakah ada sertifikat atau tidak
        $is_sertifikat = FALSE;
        foreach($syarat_array as $value){
            if(preg_match('/sertifikat/i', $value)){
                $is_sertifikat = TRUE;
            }
        }
        
        //syarat jalur rapor LENGKAP jika semua syarat terpenuhi (jumlahnya 5) atau
        //semua syarat ada kecuali sertifikat
        if(count($syarat_array) == 5 OR
                (count($syarat_array) == 4) AND !$is_sertifikat){
            return TRUE;
        }
    }
    
    
    //untuk jalur UN
    if($jalur_masuk == 'un' &&
            isset($profile['persyaratan']->field_syarat_jalur_un['und'])){
        
        $syarat_array = $profile['persyaratan']->field_syarat_jalur_un['und'];
        
        //periksa apakah ada sertifikat atau tidak
        $is_sertifikat = FALSE;
        foreach($syarat_array as $value){
            if(preg_match('/sertifikat/i', $value)){
                $is_sertifikat = TRUE;
            }
        }
        
        //syarat jalur UN LENGKAP jika semua syarat terpenuhi (jumlahnya 6) atau
        //semua syarat ada kecuali sertifikat
        if(count($syarat_array) == 6 OR
                (count($syarat_array) == 5) AND !$is_sertifikat){
            return TRUE;
        }
    }
    
    return FALSE;
}

/**
 * Membuat node KELULUSAN
 * 
 * @param $kelulusan_nid
 *  nid dari node kelulusan
 * @param $reg_nid
 *  nid dari node registration
 * @param $nilai
 *  nilai calon mahasiswa
 * @param $is_lulus
 *  apakah calon mahasiswa lulus atau tidak, tipe boolean
 * @param $kategori
 *  Reguler atau Beasiswa
 * @param $prodi_nid
 *   nid dari node Departement
 * @return
 * 
 */
function create_node_kelulusan($kelulusan_nid, $reg_nid, $nilai, $is_lulus, $kategori, $prodi_nid){
    global $user;
    
    if(empty($kelulusan_nid)){
        $kelulusan = new stdClass();
        $kelulusan->type = 'kelulusan';
        node_object_prepare($kelulusan);
        //$kelulusan->title = $username.' - '.$noreg.' - '.$is_lulus;
        $kelulusan->status = 1;
        $kelulusan->uid = $user->uid;
        $kelulusan->language = LANGUAGE_NONE;
    }
    else{
        $kelulusan = node_load($kelulusan_nid);
    }
    
    $kelulusan->field_lulus_noreg['und'][0]['target_id'] = $reg_nid;
    $kelulusan->field_lulus_nilai['und'][0]['value'] = $nilai;
    $kelulusan->field_lulus_tes['und'][0]['value'] = $is_lulus;
    $kelulusan->field_lulus_kategori['und'][0]['value'] = ($is_lulus)? $kategori:NULL;
    ($is_lulus)? $kelulusan->field_lulus_prodi['und'][0]['target_id'] = $prodi_nid:NULL;
    node_submit($kelulusan);
    node_save($kelulusan);
}

/**
 * Membuat node SURVEY
 * 
 * @param $input
 *  input dari user
 * @return
 *   
 */
function create_survey_node($input){
    global $user;
    
    $survey = node_load_multiple(array(), array('type' => 'survey', 'uid' => $user->uid));
    if(empty($survey)){
        $survey = new stdClass();
        $survey->type = 'survey';
        node_object_prepare($survey);
        //$survey->title = $username.' - '.$noreg.' - '.$is_lulus;
        $survey->status = 1;
        $survey->uid = $user->uid;
        $survey->language = LANGUAGE_NONE;
    }
    else{
        $surv = array_values($survey);
        $survey = node_load($surv[0]->nid);
    }
    
    $survey->field_survey_1['und'][0]['value'] = $input['jawab_1'];
    $survey->field_survey_2['und'][0]['value'] = $input['jawab_2'];
    $survey->field_survey_3['und'][0]['value'] = $input['jawab_3'];
    $survey->field_survey_4['und'][0]['value'] = $input['jawab_4'];
    $survey->field_survey_saran['und'][0]['value'] = $input['saran'];
    node_submit($survey);
    node_save($survey);
}