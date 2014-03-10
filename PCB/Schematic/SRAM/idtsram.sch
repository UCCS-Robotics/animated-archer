<?xml version="1.0" encoding="utf-8"?>
<!DOCTYPE eagle SYSTEM "eagle.dtd">
<eagle version="6.4">
<drawing>
<settings>
<setting alwaysvectorfont="no"/>
<setting verticaltext="up"/>
</settings>
<grid distance="0.1" unitdist="inch" unit="inch" style="lines" multiple="1" display="no" altdistance="0.01" altunitdist="inch" altunit="inch"/>
<layers>
<layer number="1" name="Top" color="4" fill="1" visible="no" active="no"/>
<layer number="16" name="Bottom" color="1" fill="1" visible="no" active="no"/>
<layer number="17" name="Pads" color="2" fill="1" visible="no" active="no"/>
<layer number="18" name="Vias" color="2" fill="1" visible="no" active="no"/>
<layer number="19" name="Unrouted" color="6" fill="1" visible="no" active="no"/>
<layer number="20" name="Dimension" color="15" fill="1" visible="no" active="no"/>
<layer number="21" name="tPlace" color="7" fill="1" visible="no" active="no"/>
<layer number="22" name="bPlace" color="7" fill="1" visible="no" active="no"/>
<layer number="23" name="tOrigins" color="15" fill="1" visible="no" active="no"/>
<layer number="24" name="bOrigins" color="15" fill="1" visible="no" active="no"/>
<layer number="25" name="tNames" color="7" fill="1" visible="no" active="no"/>
<layer number="26" name="bNames" color="7" fill="1" visible="no" active="no"/>
<layer number="27" name="tValues" color="7" fill="1" visible="no" active="no"/>
<layer number="28" name="bValues" color="7" fill="1" visible="no" active="no"/>
<layer number="29" name="tStop" color="3" fill="9" visible="no" active="no"/>
<layer number="30" name="bStop" color="7" fill="6" visible="no" active="no"/>
<layer number="31" name="tCream" color="11" fill="1" visible="no" active="no"/>
<layer number="32" name="bCream" color="7" fill="5" visible="no" active="no"/>
<layer number="33" name="tFinish" color="6" fill="3" visible="no" active="no"/>
<layer number="34" name="bFinish" color="6" fill="6" visible="no" active="no"/>
<layer number="35" name="tGlue" color="7" fill="4" visible="no" active="no"/>
<layer number="36" name="bGlue" color="7" fill="5" visible="no" active="no"/>
<layer number="37" name="tTest" color="7" fill="1" visible="no" active="no"/>
<layer number="38" name="bTest" color="7" fill="1" visible="no" active="no"/>
<layer number="39" name="tKeepout" color="13" fill="1" visible="no" active="no"/>
<layer number="40" name="bKeepout" color="5" fill="1" visible="no" active="no"/>
<layer number="41" name="tRestrict" color="4" fill="10" visible="no" active="no"/>
<layer number="42" name="bRestrict" color="1" fill="10" visible="no" active="no"/>
<layer number="43" name="vRestrict" color="2" fill="10" visible="no" active="no"/>
<layer number="44" name="Drills" color="7" fill="1" visible="no" active="no"/>
<layer number="45" name="Holes" color="7" fill="1" visible="no" active="no"/>
<layer number="46" name="Milling" color="3" fill="1" visible="no" active="no"/>
<layer number="47" name="Measures" color="7" fill="1" visible="no" active="no"/>
<layer number="48" name="Document" color="7" fill="1" visible="no" active="no"/>
<layer number="49" name="Reference" color="7" fill="1" visible="no" active="no"/>
<layer number="51" name="tDocu" color="6" fill="1" visible="no" active="no"/>
<layer number="52" name="bDocu" color="6" fill="1" visible="no" active="no"/>
<layer number="91" name="Nets" color="2" fill="1" visible="yes" active="yes"/>
<layer number="92" name="Busses" color="1" fill="1" visible="yes" active="yes"/>
<layer number="93" name="Pins" color="2" fill="1" visible="no" active="yes"/>
<layer number="94" name="Symbols" color="4" fill="1" visible="yes" active="yes"/>
<layer number="95" name="Names" color="7" fill="1" visible="yes" active="yes"/>
<layer number="96" name="Values" color="7" fill="1" visible="yes" active="yes"/>
<layer number="97" name="Info" color="7" fill="1" visible="yes" active="yes"/>
<layer number="98" name="Guide" color="6" fill="1" visible="yes" active="yes"/>
</layers>
<schematic xreflabel="%F%N/%S.%C%R" xrefpart="/%S.%C%R">
<libraries>
<library name="TSOP44-T2">
<packages>
<package name="TSOP44-T2">
<description>&lt;b&gt;IPC7351A - SOP80P1176X120-44N&lt;b&gt;</description>
<wire x1="-5.15" y1="-9.27" x2="5.15" y2="-9.27" width="0.1" layer="51"/>
<wire x1="5.15" y1="-9.27" x2="5.15" y2="9.27" width="0.1" layer="51"/>
<wire x1="5.15" y1="9.27" x2="-5.15" y2="9.27" width="0.1" layer="51"/>
<wire x1="-5.15" y1="9.27" x2="-5.15" y2="-9.27" width="0.1" layer="51"/>
<wire x1="-6.6" y1="-9.55" x2="6.6" y2="-9.55" width="0.05" layer="39"/>
<wire x1="6.6" y1="-9.55" x2="6.6" y2="9.55" width="0.05" layer="39"/>
<wire x1="6.6" y1="9.55" x2="-6.6" y2="9.55" width="0.05" layer="39"/>
<wire x1="-6.6" y1="9.55" x2="-6.6" y2="-9.55" width="0.05" layer="39"/>
<wire x1="0" y1="0.5" x2="0" y2="-0.5" width="0.05" layer="39"/>
<wire x1="0.5" y1="0" x2="-0.5" y2="0" width="0.05" layer="39"/>
<wire x1="-4.7" y1="-9.25" x2="4.7" y2="-9.25" width="0.2" layer="21"/>
<wire x1="4.7" y1="-9.25" x2="4.7" y2="9.25" width="0.2" layer="21"/>
<wire x1="4.7" y1="9.25" x2="-4.7" y2="9.25" width="0.2" layer="21"/>
<wire x1="-4.7" y1="9.25" x2="-4.7" y2="-9.25" width="0.2" layer="21"/>
<circle x="-4.15" y="8.27" radius="0.5" width="0.1" layer="51"/>
<circle x="-6.1" y="9.25" radius="0.25" width="0" layer="21"/>
<circle x="-3.7" y="8.25" radius="0.6" width="0" layer="21"/>
<smd name="1" x="-5.7" y="8.4" dx="1.25" dy="0.55" layer="1" roundness="100"/>
<smd name="2" x="-5.7" y="7.6" dx="1.25" dy="0.55" layer="1" roundness="100"/>
<smd name="3" x="-5.7" y="6.8" dx="1.25" dy="0.55" layer="1" roundness="100"/>
<smd name="4" x="-5.7" y="6" dx="1.25" dy="0.55" layer="1" roundness="100"/>
<smd name="5" x="-5.7" y="5.2" dx="1.25" dy="0.55" layer="1" roundness="100"/>
<smd name="6" x="-5.7" y="4.4" dx="1.25" dy="0.55" layer="1" roundness="100"/>
<smd name="7" x="-5.7" y="3.6" dx="1.25" dy="0.55" layer="1" roundness="100"/>
<smd name="8" x="-5.7" y="2.8" dx="1.25" dy="0.55" layer="1" roundness="100"/>
<smd name="9" x="-5.7" y="2" dx="1.25" dy="0.55" layer="1" roundness="100"/>
<smd name="10" x="-5.7" y="1.2" dx="1.25" dy="0.55" layer="1" roundness="100"/>
<smd name="11" x="-5.7" y="0.4" dx="1.25" dy="0.55" layer="1" roundness="100"/>
<smd name="12" x="-5.7" y="-0.4" dx="1.25" dy="0.55" layer="1" roundness="100"/>
<smd name="13" x="-5.7" y="-1.2" dx="1.25" dy="0.55" layer="1" roundness="100"/>
<smd name="14" x="-5.7" y="-2" dx="1.25" dy="0.55" layer="1" roundness="100"/>
<smd name="15" x="-5.7" y="-2.8" dx="1.25" dy="0.55" layer="1" roundness="100"/>
<smd name="16" x="-5.7" y="-3.6" dx="1.25" dy="0.55" layer="1" roundness="100"/>
<smd name="17" x="-5.7" y="-4.4" dx="1.25" dy="0.55" layer="1" roundness="100"/>
<smd name="18" x="-5.7" y="-5.2" dx="1.25" dy="0.55" layer="1" roundness="100"/>
<smd name="19" x="-5.7" y="-6" dx="1.25" dy="0.55" layer="1" roundness="100"/>
<smd name="20" x="-5.7" y="-6.8" dx="1.25" dy="0.55" layer="1" roundness="100"/>
<smd name="21" x="-5.7" y="-7.6" dx="1.25" dy="0.55" layer="1" roundness="100"/>
<smd name="22" x="-5.7" y="-8.4" dx="1.25" dy="0.55" layer="1" roundness="100"/>
<smd name="23" x="5.7" y="-8.4" dx="1.25" dy="0.55" layer="1" roundness="100"/>
<smd name="24" x="5.7" y="-7.6" dx="1.25" dy="0.55" layer="1" roundness="100"/>
<smd name="25" x="5.7" y="-6.8" dx="1.25" dy="0.55" layer="1" roundness="100"/>
<smd name="26" x="5.7" y="-6" dx="1.25" dy="0.55" layer="1" roundness="100"/>
<smd name="27" x="5.7" y="-5.2" dx="1.25" dy="0.55" layer="1" roundness="100"/>
<smd name="28" x="5.7" y="-4.4" dx="1.25" dy="0.55" layer="1" roundness="100"/>
<smd name="29" x="5.7" y="-3.6" dx="1.25" dy="0.55" layer="1" roundness="100"/>
<smd name="30" x="5.7" y="-2.8" dx="1.25" dy="0.55" layer="1" roundness="100"/>
<smd name="31" x="5.7" y="-2" dx="1.25" dy="0.55" layer="1" roundness="100"/>
<smd name="32" x="5.7" y="-1.2" dx="1.25" dy="0.55" layer="1" roundness="100"/>
<smd name="33" x="5.7" y="-0.4" dx="1.25" dy="0.55" layer="1" roundness="100"/>
<smd name="34" x="5.7" y="0.4" dx="1.25" dy="0.55" layer="1" roundness="100"/>
<smd name="35" x="5.7" y="1.2" dx="1.25" dy="0.55" layer="1" roundness="100"/>
<smd name="36" x="5.7" y="2" dx="1.25" dy="0.55" layer="1" roundness="100"/>
<smd name="37" x="5.7" y="2.8" dx="1.25" dy="0.55" layer="1" roundness="100"/>
<smd name="38" x="5.7" y="3.6" dx="1.25" dy="0.55" layer="1" roundness="100"/>
<smd name="39" x="5.7" y="4.4" dx="1.25" dy="0.55" layer="1" roundness="100"/>
<smd name="40" x="5.7" y="5.2" dx="1.25" dy="0.55" layer="1" roundness="100"/>
<smd name="41" x="5.7" y="6" dx="1.25" dy="0.55" layer="1" roundness="100"/>
<smd name="42" x="5.7" y="6.8" dx="1.25" dy="0.55" layer="1" roundness="100"/>
<smd name="43" x="5.7" y="7.6" dx="1.25" dy="0.55" layer="1" roundness="100"/>
<smd name="44" x="5.7" y="8.4" dx="1.25" dy="0.55" layer="1" roundness="100"/>
<text x="-1.27" y="0" size="0.7" layer="25" ratio="5" rot="R90">&gt;NAME</text>
<text x="1.27" y="0" size="0.7" layer="27" ratio="5" rot="R90">&gt;VALUE</text>
<text x="0" y="0" size="0.7" layer="51" ratio="5" rot="R90">&gt;NAME</text>
</package>
</packages>
<symbols>
<symbol name="TSOP44">
<wire x1="-25.4" y1="15.24" x2="-2.54" y2="15.24" width="0.254" layer="94"/>
<wire x1="-2.54" y1="15.24" x2="-2.54" y2="-43.18" width="0.254" layer="94"/>
<wire x1="-25.4" y1="-43.18" x2="-25.4" y2="15.24" width="0.254" layer="94"/>
<pin name="NC" x="-30.48" y="12.7" length="middle"/>
<pin name="NC@1" x="-30.48" y="10.16" length="middle"/>
<pin name="A0" x="-30.48" y="7.62" length="middle"/>
<pin name="A1" x="-30.48" y="5.08" length="middle"/>
<pin name="A2" x="-30.48" y="2.54" length="middle"/>
<pin name="A3" x="-30.48" y="0" length="middle"/>
<pin name="A4" x="-30.48" y="-2.54" length="middle"/>
<pin name="CS" x="-30.48" y="-5.08" length="middle"/>
<pin name="I/00" x="-30.48" y="-7.62" length="middle"/>
<pin name="I/01" x="-30.48" y="-10.16" length="middle"/>
<pin name="VDD" x="-30.48" y="-12.7" length="middle"/>
<pin name="VSS" x="-30.48" y="-15.24" length="middle"/>
<pin name="I/02" x="-30.48" y="-17.78" length="middle"/>
<pin name="I/03" x="-30.48" y="-20.32" length="middle"/>
<pin name="WE" x="-30.48" y="-22.86" length="middle"/>
<pin name="A5" x="-30.48" y="-25.4" length="middle"/>
<pin name="A6" x="-30.48" y="-27.94" length="middle"/>
<pin name="A7" x="-30.48" y="-30.48" length="middle"/>
<pin name="A8" x="-30.48" y="-33.02" length="middle"/>
<pin name="A9" x="-30.48" y="-35.56" length="middle"/>
<pin name="NC@2" x="-30.48" y="-38.1" length="middle"/>
<wire x1="-25.4" y1="-43.18" x2="-2.54" y2="-43.18" width="0.254" layer="94"/>
<pin name="NC@3" x="-30.48" y="-40.64" length="middle"/>
<pin name="NC@4" x="2.54" y="-40.64" length="middle" rot="R180"/>
<pin name="NC@5" x="2.54" y="-38.1" length="middle" rot="R180"/>
<pin name="NC@6" x="2.54" y="-35.56" length="middle" rot="R180"/>
<pin name="A10" x="2.54" y="-33.02" length="middle" rot="R180"/>
<pin name="A11" x="2.54" y="-30.48" length="middle" rot="R180"/>
<pin name="A12" x="2.54" y="-27.94" length="middle" rot="R180"/>
<pin name="A13" x="2.54" y="-25.4" length="middle" rot="R180"/>
<pin name="A14" x="2.54" y="-22.86" length="middle" rot="R180"/>
<pin name="I/04" x="2.54" y="-20.32" length="middle" rot="R180"/>
<pin name="I/05" x="2.54" y="-17.78" length="middle" rot="R180"/>
<pin name="VDD@2" x="2.54" y="-15.24" length="middle" rot="R180"/>
<pin name="VSS@2" x="2.54" y="-12.7" length="middle" rot="R180"/>
<pin name="I/06" x="2.54" y="-10.16" length="middle" rot="R180"/>
<pin name="I/07" x="2.54" y="-7.62" length="middle" rot="R180"/>
<pin name="OE" x="2.54" y="-5.08" length="middle" rot="R180"/>
<pin name="A15" x="2.54" y="-2.54" length="middle" rot="R180"/>
<pin name="A16" x="2.54" y="0" length="middle" rot="R180"/>
<pin name="A17" x="2.54" y="2.54" length="middle" rot="R180"/>
<pin name="A18" x="2.54" y="5.08" length="middle" rot="R180"/>
<pin name="NC@7" x="2.54" y="7.62" length="middle" rot="R180"/>
<pin name="NC@8" x="2.54" y="10.16" length="middle" rot="R180"/>
<pin name="NC@9" x="2.54" y="12.7" length="middle" rot="R180"/>
</symbol>
</symbols>
<devicesets>
<deviceset name="IDT71V424S15PHGI8">
<description>IDT71V424S15PHGI8
3.3V CMOS Static RAM
4 Meg (512K x 8-Bit)</description>
<gates>
<gate name="G$1" symbol="TSOP44" x="15.24" y="12.7"/>
</gates>
<devices>
<device name="" package="TSOP44-T2">
<connects>
<connect gate="G$1" pin="A0" pad="3"/>
<connect gate="G$1" pin="A1" pad="4"/>
<connect gate="G$1" pin="A10" pad="26"/>
<connect gate="G$1" pin="A11" pad="27"/>
<connect gate="G$1" pin="A12" pad="28"/>
<connect gate="G$1" pin="A13" pad="29"/>
<connect gate="G$1" pin="A14" pad="30"/>
<connect gate="G$1" pin="A15" pad="38"/>
<connect gate="G$1" pin="A16" pad="39"/>
<connect gate="G$1" pin="A17" pad="40"/>
<connect gate="G$1" pin="A18" pad="41"/>
<connect gate="G$1" pin="A2" pad="5"/>
<connect gate="G$1" pin="A3" pad="6"/>
<connect gate="G$1" pin="A4" pad="7"/>
<connect gate="G$1" pin="A5" pad="16"/>
<connect gate="G$1" pin="A6" pad="17"/>
<connect gate="G$1" pin="A7" pad="18"/>
<connect gate="G$1" pin="A8" pad="19"/>
<connect gate="G$1" pin="A9" pad="20"/>
<connect gate="G$1" pin="CS" pad="8"/>
<connect gate="G$1" pin="I/00" pad="9"/>
<connect gate="G$1" pin="I/01" pad="10"/>
<connect gate="G$1" pin="I/02" pad="13"/>
<connect gate="G$1" pin="I/03" pad="14"/>
<connect gate="G$1" pin="I/04" pad="31"/>
<connect gate="G$1" pin="I/05" pad="32"/>
<connect gate="G$1" pin="I/06" pad="35"/>
<connect gate="G$1" pin="I/07" pad="36"/>
<connect gate="G$1" pin="NC" pad="1"/>
<connect gate="G$1" pin="NC@1" pad="2"/>
<connect gate="G$1" pin="NC@2" pad="21"/>
<connect gate="G$1" pin="NC@3" pad="22"/>
<connect gate="G$1" pin="NC@4" pad="23"/>
<connect gate="G$1" pin="NC@5" pad="24"/>
<connect gate="G$1" pin="NC@6" pad="25"/>
<connect gate="G$1" pin="NC@7" pad="42"/>
<connect gate="G$1" pin="NC@8" pad="43"/>
<connect gate="G$1" pin="NC@9" pad="44"/>
<connect gate="G$1" pin="OE" pad="37"/>
<connect gate="G$1" pin="VDD" pad="11"/>
<connect gate="G$1" pin="VDD@2" pad="33"/>
<connect gate="G$1" pin="VSS" pad="12"/>
<connect gate="G$1" pin="VSS@2" pad="34"/>
<connect gate="G$1" pin="WE" pad="15"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
</libraries>
<attributes>
</attributes>
<variantdefs>
</variantdefs>
<classes>
<class number="0" name="default" width="0" drill="0">
</class>
</classes>
<parts>
<part name="U$1" library="TSOP44-T2" deviceset="IDT71V424S15PHGI8" device=""/>
</parts>
<sheets>
<sheet>
<plain>
</plain>
<instances>
<instance part="U$1" gate="G$1" x="63.5" y="50.8"/>
</instances>
<busses>
</busses>
<nets>
<net name="3.3V" class="0">
<segment>
<pinref part="U$1" gate="G$1" pin="VDD"/>
<wire x1="33.02" y1="38.1" x2="15.24" y2="38.1" width="0.1524" layer="91"/>
<label x="15.24" y="38.1" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="U$1" gate="G$1" pin="VDD@2"/>
<wire x1="66.04" y1="35.56" x2="86.36" y2="35.56" width="0.1524" layer="91"/>
<label x="78.74" y="35.56" size="1.778" layer="95"/>
</segment>
</net>
<net name="GND" class="0">
<segment>
<pinref part="U$1" gate="G$1" pin="VSS@2"/>
<wire x1="66.04" y1="38.1" x2="93.98" y2="38.1" width="0.1524" layer="91"/>
<label x="86.36" y="38.1" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="U$1" gate="G$1" pin="VSS"/>
<wire x1="33.02" y1="35.56" x2="2.54" y2="35.56" width="0.1524" layer="91"/>
<label x="5.08" y="35.56" size="1.778" layer="95"/>
</segment>
</net>
</nets>
</sheet>
</sheets>
</schematic>
</drawing>
</eagle>
