<?php

function daftar_rekap_peserta(){
    global $base_path;
    $output = '';
    $img_path = $base_path.'sites/default/files/univbakrie.jpg';
    
   
    $output .= "<table border='0' width='100%' cellspacing='0' cellpadding='0' bordercolor='#C0C0C0' style='border-width:0px; '>
	<tbody><tr>
		<td style='border-left-style: none; border-left-width: medium; border-right-style: none; border-right-width: medium; border-top-style: none; border-top-width: medium' colspan='15'>
		<img border='0' src='$img_path' width='150' height='42'></td>
	</tr>
	<tr>
		<td style='border-left-style: none; border-left-width: medium; border-right-style: none; border-right-width: medium; border-top-style: none; border-top-width: medium' colspan='15'>
                <h3>Jalur USM</h3>
                </td>
	</tr>
	<tr>
		<td style='border-style: solid; border-width: 1px' width='4%' align='right' bgcolor='#C0C0C0'>
		<p style='margin:2px 5px; '>
		<b>
		<font size='2' face='Verdana'>NO</font></b></p></td>
		<td style='border-right-style: solid; border-right-width: 1px; border-top-style: solid; border-top-width: 1px; border-bottom-style: solid; border-bottom-width: 1px' bgcolor='#C0C0C0'>
		<p style='margin:2px 5px; '>
		<b>
		<font size='2' face='Verdana'>AREA TEST</font></b></p></td>
		<td style='border-right-style: solid; border-right-width: 1px; border-top-style: solid; border-top-width: 1px; border-bottom-style: solid; border-bottom-width: 1px' bgcolor='#C0C0C0'>
		<p style='margin:2px 5px; '><b>
		<font size='2' face='Verdana'>GEL.</font></b></p></td>
		<td style='border-right-style: solid; border-right-width: 1px; border-top-style: solid; border-top-width: 1px; border-bottom-style: solid; border-bottom-width: 1px' bgcolor='#C0C0C0'>
		<p style='margin:2px 5px; '><b>
		<font size='2' face='Verdana'>TGL</font></b></p></td>";
    
    $depts = node_load_multiple(array(),array('type' => 'departement'));
    
    $prodi_urut = array();
    foreach($depts as $prodi){
        $prodi_urut[$prodi->nid] = $prodi->field_departement_priority['und'][0]['value'];
    }
    //urutkan program studi sesuai prioritas
    asort($prodi_urut);
    
    $departements = array();
    foreach($prodi_urut as $key => $value){
        $dept = node_load($key);
        $kode_dept = strtoupper($dept->field_departement_code['und'][0]['value']);
        $output .=     
		"<td style='border-right-style: solid; border-right-width: 1px; border-top-style: solid; border-top-width: 1px; border-bottom-style: solid; border-bottom-width: 1px' bgcolor='#C0C0C0'>
		<p style='margin:2px 5px; '>
		<b>
		<font size='2' face='Verdana'>$kode_dept</font></b></p></td>";
        
        //save dept's code and name in array for verivication a candidate later
        $departements[$kode_dept] = $dept->nid;
    }
                         
       $output .=
            "<td style='border-right-style: solid; border-right-width: 1px; border-top-style: solid; border-top-width: 1px; border-bottom-style: solid; border-bottom-width: 1px' bgcolor='#C0C0C0'>
            <p style='margin:2px 5px; '><b>
            <font size='2' face='Verdana'>TOTAL</font></b></p></td>
        </tr>";
	
       $schedules = node_load_multiple(array(),array('type' => 'schedule'));
       $schedule_usm = array();
       $schedule_rapor = array();
       $schedule_un = array();
       
       //simpan ke 3 variable yang berbeda untuk kategori usm, rapor, dan un
       foreach($schedules as $sch_node){
           $kategori = $sch_node->field_schedule_kategori['und'][0]['value'];
           if(preg_match('/jalur usm/i', $kategori)){
               $schedule_usm[] = $sch_node;
           }
           
           if(preg_match('/jalur rapor/i', $kategori)){
               $schedule_rapor[] = $sch_node;
           }
           
           if(preg_match('/jalur un/i', $kategori)){
               $schedule_un[] = $sch_node;
           }
       }
       
       $output .= daftar_peserta_usm($schedule_usm, $departements);
       $output .= daftar_peserta_rapor($schedule_rapor);
       $output .= daftar_peserta_un($schedule_un);
          
    return $output;
}

//Table Rekap Jalur USM
function daftar_peserta_usm($schedule_usm, $departements){
    $output = '';
    
    //JALUR USM
       $total_perprodi = 0;
       $jumlah_peserta = array();
       $no = 1;
       foreach($schedule_usm as $sch_usm){
           $kota = $sch_usm->field_schedule_city['und'][0]['value'];
           $gelombang = $sch_usm->field_schedule_gelombang['und'][0]['value'];
           $tanggal_test = date('d M Y', strtotime($sch_usm->field_schedule_waktu['und'][0]['value']));
           
           //set background color
           $bgcolor = '#FFFFFF';
           if($no%2 == 0){
               $bgcolor = '#FFFFCC';
           }
           
           $output .= 
               "<tr><td style='border-left-style: solid; border-left-width: 1px; border-right-style: solid; border-right-width: 1px; border-bottom-style: solid; border-bottom-width: 1px' width='4%' align='right' bgcolor='$bgcolor'>
                    <p style='margin:2px 5px; '>
                    <font size='2' face='Verdana'>$no.</font></p></td>
                    <td style='border-right-style: solid; border-right-width: 1px; border-bottom-style: solid; border-bottom-width: 1px'  bgcolor='$bgcolor'>
                    <p style='margin:2px 5px; '>
                    <font size='2' face='Verdana'>$kota</font></p></td>

                    <td style='border-right-style: solid; border-right-width: 1px; border-bottom-style: solid; border-bottom-width: 1px' align='right' bgcolor='$bgcolor'>
                    <p style='margin:2px 5px; '>
                    <font size='2' face='Verdana'>$gelombang</font></p></td>
                    <td style='border-right-style: solid; border-right-width: 1px; border-bottom-style: solid; border-bottom-width: 1px' align='left'  bgcolor='$bgcolor'>
                    <p style='margin:2px 5px; '>
                    <font size='2' face='Verdana'>$tanggal_test</font></p></td>";
           
           $total = 0;
           //hitung jumlah peserta berdasarkan program studi
           foreach($departements as $dept_nid){
                $query = new EntityFieldQuery();
                $query->entityCondition('entity_type', 'node')
                        ->entityCondition('bundle', 'registration')
                        ->propertyCondition('status', 1)         
                        ->fieldCondition('field_reg_schedule', 'target_id', $sch_usm->nid , '=')
                        ->fieldCondition('field_reg_departement1', 'target_id', $dept_nid , '=');;
                $result = $query->execute();
                              
                if(isset($result['node'])){
                    $jumlah = count($result['node']);
                }
                else{
                    $jumlah = 0;
                }
                
                $output .= "<td style='border-right-style: solid; border-right-width: 1px; border-bottom-style: solid; border-bottom-width: 1px' align='right'  bgcolor='$bgcolor'>
                    <p style='margin:2px 5px; '>
                    <font size='2' face='Verdana'>$jumlah</font></p></td>";
                
                //inisialisasi
                $jumlah_peserta[$dept_nid] = 
                        isset($jumlah_peserta[$dept_nid])? $jumlah_peserta[$dept_nid]: 0;
                $jumlah_peserta[$dept_nid] += $jumlah;
                
                $total += $jumlah;
           }
           
           $output .= "<td style='border-right-style: solid; border-right-width: 1px; border-bottom-style: solid; border-bottom-width: 1px' align='right' bgcolor='$bgcolor'>
                    <p style='margin:2px 5px; '>
                    <font size='2' face='Verdana'><b>$total</b></font></p></td>";
           
           $output .= "</tr>";
           
           $no++;
           
           //hitung total peserta per program studi
           $total_perprodi += $total;
       }
       
       $output .= "<tr>
		<td style='border-style:none; border-width:medium; ' width='4%' align='right'>
		<p style='margin-left: 5px; margin-right: 5px'>&nbsp;</p></td>
		<td style='border-style:none; border-width:medium; '>
		<p style='margin-left: 5px; margin-right: 5px'>&nbsp;</p></td>
		<td style='border-style:none; border-width:medium; ' align='right'>
		&nbsp;</td>
		<td style='border-right-style: solid; border-right-width: 1px; border-bottom-style: none; border-bottom-width: medium; border-left-style:none; border-left-width:medium; border-top-style:none; border-top-width:medium' align='right'>
		&nbsp;</td>";
       
       $total_peserta = 0;
       foreach($jumlah_peserta as $jumlah_perprodi){
           $output .= "<td style='border-right-style: solid; border-right-width: 1px; border-bottom-style: solid; border-bottom-width: 1px' align='right'>
		<p style='margin-left: 5px; margin-right: 5px'>
		<b>
		<font size='2' face='Verdana'>$jumlah_perprodi</font></b></p></td>";
           
           $total_peserta += $jumlah_perprodi;
       }
           $output .=
	"
		<td style='border-right-style: solid; border-right-width: 1px; border-bottom-style: solid; border-bottom-width: 1px' align='right'>
		<p style='margin-left: 5px; margin-right: 5px'><b>
		<font size='2' face='Verdana'>$total_peserta</font></b></p></td>
	</tr>
	</tbody></table>";
           
    
   return $output;
}


//Table Rekap Jalur Rapor
function daftar_peserta_rapor($schedule_rapor){
    $output = '<h3>Jalur Rapor</h3>';
     $output .= "<table border='0' width='100%' cellspacing='0' cellpadding='0' bordercolor='#C0C0C0' style='border-width:0px; '>
	<tbody>
	<tr>
		<td style='border-left-style: none; border-left-width: medium; border-right-style: none; border-right-width: medium; border-top-style: none; border-top-width: medium' colspan='15'>&nbsp;</td>
	</tr>
	<tr>
		<td style='border-style: solid; border-width: 1px' width='4%' align='right' bgcolor='#C0C0C0'>
		<p style='margin:2px 5px; '>
		<b>
		<font size='2' face='Verdana'>NO</font></b></p></td>		
		<td style='border-right-style: solid; border-right-width: 1px; border-top-style: solid; border-top-width: 1px; border-bottom-style: solid; border-bottom-width: 1px' bgcolor='#C0C0C0'>
		<p style='margin:2px 5px; '><b>
		<font size='2' face='Verdana'>GEL.</font></b></p></td>
		<td style='border-right-style: solid; border-right-width: 1px; border-top-style: solid; border-top-width: 1px; border-bottom-style: solid; border-bottom-width: 1px' bgcolor='#C0C0C0'>
		<p style='margin:2px 5px; '><b>
		<font size='2' face='Verdana'>Penyerahan Dokumen</font></b></p></td>";
    
    $depts = node_load_multiple(array(),array('type' => 'departement'));
    $prodi_urut = array();
    foreach($depts as $prodi){
        $prodi_urut[$prodi->nid] = $prodi->field_departement_priority['und'][0]['value'];
    }
    //urutkan program studi sesuai prioritas
    asort($prodi_urut);
    
    $departements = array();    
    foreach($prodi_urut as $key => $value){
        $dept = node_load($key);
        $kode_dept = strtoupper($dept->field_departement_code['und'][0]['value']);
        $output .=     
		"<td style='border-right-style: solid; border-right-width: 1px; border-top-style: solid; border-top-width: 1px; border-bottom-style: solid; border-bottom-width: 1px' bgcolor='#C0C0C0'>
		<p style='margin:2px 5px; '>
		<b>
		<font size='2' face='Verdana'>$kode_dept</font></b></p></td>";
        
        //save dept's code and name in array for verivication a candidate later
        $departements[$kode_dept] = $dept->nid;
    }
                         
       $output .=
            "<td style='border-right-style: solid; border-right-width: 1px; border-top-style: solid; border-top-width: 1px; border-bottom-style: solid; border-bottom-width: 1px' bgcolor='#C0C0C0'>
            <p style='margin:2px 5px; '><b>
            <font size='2' face='Verdana'>TOTAL</font></b></p></td>
        </tr>";
	
    //JALUR Rapor
       $total_perprodi = 0;
       $jumlah_peserta = array();
       $no = 1;
       foreach($schedule_rapor as $sch_rapor){         
           $gelombang = $sch_rapor->field_schedule_gelombang['und'][0]['value'];
           $penyerahan_doc = date('d M Y', strtotime($sch_rapor->field_schedule_document['und'][0]['value']));
           
           //set background color
           $bgcolor = '#FFFFFF';
           if($no%2 == 0){
               $bgcolor = '#FFFFCC';
           }
           
           $output .= 
               "<tr><td style='border-left-style: solid; border-left-width: 1px; border-right-style: solid; border-right-width: 1px; border-bottom-style: solid; border-bottom-width: 1px' width='4%' align='right' bgcolor='$bgcolor'>
                    <p style='margin:2px 5px; '>
                    <font size='2' face='Verdana'>$no.</font></p></td>

                    <td style='border-right-style: solid; border-right-width: 1px; border-bottom-style: solid; border-bottom-width: 1px' align='right' bgcolor='$bgcolor'>
                    <p style='margin:2px 5px; '>
                    <font size='2' face='Verdana'>$gelombang</font></p></td>
                    <td style='border-right-style: solid; border-right-width: 1px; border-bottom-style: solid; border-bottom-width: 1px' align='left'  bgcolor='$bgcolor'>
                    <p style='margin:2px 5px; '>
                    <font size='2' face='Verdana'>$penyerahan_doc</font></p></td>";
           
           $total = 0;
           //hitung jumlah peserta berdasarkan program studi
           foreach($departements as $dept_nid){
                $query = new EntityFieldQuery();
                $query->entityCondition('entity_type', 'node')
                        ->entityCondition('bundle', 'registration')
                        ->propertyCondition('status', 1)         
                        ->fieldCondition('field_reg_schedule', 'target_id', $sch_rapor->nid , '=')
                        ->fieldCondition('field_reg_departement1', 'target_id', $dept_nid , '=');;
                $result = $query->execute();
                              
                if(isset($result['node'])){
                    $jumlah = count($result['node']);
                }
                else{
                    $jumlah = 0;
                }
                
                $output .= "<td style='border-right-style: solid; border-right-width: 1px; border-bottom-style: solid; border-bottom-width: 1px' align='right'  bgcolor='$bgcolor'>
                    <p style='margin:2px 5px; '>
                    <font size='2' face='Verdana'>$jumlah</font></p></td>";
                
                //inisialisasi
                $jumlah_peserta[$dept_nid] = 
                        isset($jumlah_peserta[$dept_nid])? $jumlah_peserta[$dept_nid]: 0;
                $jumlah_peserta[$dept_nid] += $jumlah;
                
                $total += $jumlah;
           }
           
           $output .= "<td style='border-right-style: solid; border-right-width: 1px; border-bottom-style: solid; border-bottom-width: 1px' align='right' bgcolor='$bgcolor'>
                    <p style='margin:2px 5px; '>
                    <font size='2' face='Verdana'><b>$total</b></font></p></td>";
           
           $output .= "</tr>";
           
           $no++;
           
           //hitung total peserta per program studi
           $total_perprodi += $total;
       }
       
       $output .= "<tr>
		<td style='border-style:none; border-width:medium; ' width='4%' align='right'>
		<p style='margin-left: 5px; margin-right: 5px'>&nbsp;</p></td>
		<td style='border-style:none; border-width:medium; '>
		<p style='margin-left: 5px; margin-right: 5px'>&nbsp;</p></td>
		
		<td style='border-right-style: solid; border-right-width: 1px; border-bottom-style: none; border-bottom-width: medium; border-left-style:none; border-left-width:medium; border-top-style:none; border-top-width:medium' align='right'>
		&nbsp;</td>";
       
       $total_peserta = 0;
       foreach($jumlah_peserta as $jumlah_perprodi){
           $output .= "<td style='border-right-style: solid; border-right-width: 1px; border-bottom-style: solid; border-bottom-width: 1px' align='right'>
		<p style='margin-left: 5px; margin-right: 5px'>
		<b>
		<font size='2' face='Verdana'>$jumlah_perprodi</font></b></p></td>";
           
           $total_peserta += $jumlah_perprodi;
       }
           $output .=
	"
		<td style='border-right-style: solid; border-right-width: 1px; border-bottom-style: solid; border-bottom-width: 1px' align='right'>
		<p style='margin-left: 5px; margin-right: 5px'><b>
		<font size='2' face='Verdana'>$total_peserta</font></b></p></td>
	</tr>
	</tbody></table>";
           
    
   return $output;
}


//Table Rekap Jalur UN
function daftar_peserta_un($schedule_un){
    $output = '<h3>Jalur UN</h3>';
     $output .= "<table border='0' width='100%' cellspacing='0' cellpadding='0' bordercolor='#C0C0C0' style='border-width:0px; '>
	<tbody>
	<tr>
		<td style='border-left-style: none; border-left-width: medium; border-right-style: none; border-right-width: medium; border-top-style: none; border-top-width: medium' colspan='15'>&nbsp;</td>
	</tr>
	<tr>
		<td style='border-style: solid; border-width: 1px' width='4%' align='right' bgcolor='#C0C0C0'>
		<p style='margin:2px 5px; '>
		<b>
		<font size='2' face='Verdana'>NO</font></b></p></td>		
		<td style='border-right-style: solid; border-right-width: 1px; border-top-style: solid; border-top-width: 1px; border-bottom-style: solid; border-bottom-width: 1px' bgcolor='#C0C0C0'>
		<p style='margin:2px 5px; '><b>
		<font size='2' face='Verdana'>GEL.</font></b></p></td>
		<td style='border-right-style: solid; border-right-width: 1px; border-top-style: solid; border-top-width: 1px; border-bottom-style: solid; border-bottom-width: 1px' bgcolor='#C0C0C0'>
		<p style='margin:2px 5px; '><b>
		<font size='2' face='Verdana'>Penyerahan Dokumen</font></b></p></td>";
    
    $depts = node_load_multiple(array(),array('type' => 'departement'));
    $prodi_urut = array();
    foreach($depts as $prodi){
        $prodi_urut[$prodi->nid] = $prodi->field_departement_priority['und'][0]['value'];
    }
    //urutkan program studi sesuai prioritas
    asort($prodi_urut);
    
    $departements = array();    
    foreach($prodi_urut as $key => $value){
        $dept = node_load($key);
        $kode_dept = strtoupper($dept->field_departement_code['und'][0]['value']);
        $output .=     
		"<td style='border-right-style: solid; border-right-width: 1px; border-top-style: solid; border-top-width: 1px; border-bottom-style: solid; border-bottom-width: 1px' bgcolor='#C0C0C0'>
		<p style='margin:2px 5px; '>
		<b>
		<font size='2' face='Verdana'>$kode_dept</font></b></p></td>";
        
        //save dept's code and name in array for verivication a candidate later
        $departements[$kode_dept] = $dept->nid;
    }
                         
       $output .=
            "<td style='border-right-style: solid; border-right-width: 1px; border-top-style: solid; border-top-width: 1px; border-bottom-style: solid; border-bottom-width: 1px' bgcolor='#C0C0C0'>
            <p style='margin:2px 5px; '><b>
            <font size='2' face='Verdana'>TOTAL</font></b></p></td>
        </tr>";
	
    //JALUR UN
       $total_perprodi = 0;
       $jumlah_peserta = array();
       $no = 1;
       foreach($schedule_un as $sch_un){         
           $gelombang = $sch_un->field_schedule_gelombang['und'][0]['value'];
           $penyerahan_doc = date('d M Y', strtotime($sch_un->field_schedule_document['und'][0]['value']));
           
           //set background color
           $bgcolor = '#FFFFFF';
           if($no%2 == 0){
               $bgcolor = '#FFFFCC';
           }
           
           $output .= 
               "<tr><td style='border-left-style: solid; border-left-width: 1px; border-right-style: solid; border-right-width: 1px; border-bottom-style: solid; border-bottom-width: 1px' width='4%' align='right' bgcolor='$bgcolor'>
                    <p style='margin:2px 5px; '>
                    <font size='2' face='Verdana'>$no.</font></p></td>

                    <td style='border-right-style: solid; border-right-width: 1px; border-bottom-style: solid; border-bottom-width: 1px' align='right' bgcolor='$bgcolor'>
                    <p style='margin:2px 5px; '>
                    <font size='2' face='Verdana'>$gelombang</font></p></td>
                    <td style='border-right-style: solid; border-right-width: 1px; border-bottom-style: solid; border-bottom-width: 1px' align='left'  bgcolor='$bgcolor'>
                    <p style='margin:2px 5px; '>
                    <font size='2' face='Verdana'>$penyerahan_doc</font></p></td>";
           
           $total = 0;
           //hitung jumlah peserta berdasarkan program studi
           foreach($departements as $dept_nid){
                $query = new EntityFieldQuery();
                $query->entityCondition('entity_type', 'node')
                        ->entityCondition('bundle', 'registration')
                        ->propertyCondition('status', 1)         
                        ->fieldCondition('field_reg_schedule', 'target_id', $sch_un->nid , '=')
                        ->fieldCondition('field_reg_departement1', 'target_id', $dept_nid , '=');;
                $result = $query->execute();
                              
                if(isset($result['node'])){
                    $jumlah = count($result['node']);
                }
                else{
                    $jumlah = 0;
                }
                
                $output .= "<td style='border-right-style: solid; border-right-width: 1px; border-bottom-style: solid; border-bottom-width: 1px' align='right'  bgcolor='$bgcolor'>
                    <p style='margin:2px 5px; '>
                    <font size='2' face='Verdana'>$jumlah</font></p></td>";
                
                //inisialisasi
                $jumlah_peserta[$dept_nid] = 
                        isset($jumlah_peserta[$dept_nid])? $jumlah_peserta[$dept_nid]: 0;
                $jumlah_peserta[$dept_nid] += $jumlah;
                
                $total += $jumlah;
           }
           
           $output .= "<td style='border-right-style: solid; border-right-width: 1px; border-bottom-style: solid; border-bottom-width: 1px' align='right' bgcolor='$bgcolor'>
                    <p style='margin:2px 5px; '>
                    <font size='2' face='Verdana'><b>$total</b></font></p></td>";
           
           $output .= "</tr>";
           
           $no++;
           
           //hitung total peserta per program studi
           $total_perprodi += $total;
       }
       
       $output .= "<tr>
		<td style='border-style:none; border-width:medium; ' width='4%' align='right'>
		<p style='margin-left: 5px; margin-right: 5px'>&nbsp;</p></td>
		<td style='border-style:none; border-width:medium; '>
		<p style='margin-left: 5px; margin-right: 5px'>&nbsp;</p></td>
		
		<td style='border-right-style: solid; border-right-width: 1px; border-bottom-style: none; border-bottom-width: medium; border-left-style:none; border-left-width:medium; border-top-style:none; border-top-width:medium' align='right'>
		&nbsp;</td>";
       
       $total_peserta = 0;
       foreach($jumlah_peserta as $jumlah_perprodi){
           $output .= "<td style='border-right-style: solid; border-right-width: 1px; border-bottom-style: solid; border-bottom-width: 1px' align='right'>
		<p style='margin-left: 5px; margin-right: 5px'>
		<b>
		<font size='2' face='Verdana'>$jumlah_perprodi</font></b></p></td>";
           
           $total_peserta += $jumlah_perprodi;
       }
           $output .=
	"
		<td style='border-right-style: solid; border-right-width: 1px; border-bottom-style: solid; border-bottom-width: 1px' align='right'>
		<p style='margin-left: 5px; margin-right: 5px'><b>
		<font size='2' face='Verdana'>$total_peserta</font></b></p></td>
	</tr>
	</tbody></table>";
           
    
   return $output;
}